__copyright__ = """
COPYRIGHT:
  Copyright (c) 2016    PANDA(yaxi1984@gmail.com)    All rights reserved.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
  MA 02111-1307 USA
"""

__description__ = """
DESCRIPTION:
 A tool to convert memmap excel file to memcfg binary file.
"""

__usage__ = """
USAGE:
 memcfg_converter <options>

 <options> definition:
  --input=<path>   : Input memmap file path;
  --output=<path>  : Output memcfg binary file path;
  --pad-to=<len>   : (optional)
                     Pad output binary file length to <len> bytes;
                      no padding, if this option is missing;
  --pad-val=<val>  : (optional)
                     Padding with <val>;
                      0xFF will be used as default, if this option is missing;
  --page-size=<val>: (optional)
                     Flash page size; (unit of byte)
                      0x200 will be used as default, if this option is missing;
"""

__history__ = """
HISTORY:
 v1.0.0        2016/3/1         Panda.Xiong
   Initially created.

 v1.1.0        2016/4/25        Panda.Xiong
   Force reset bit[0] of last byte for each flash page,
    to indicate all flash page contents are ready,
    to support recoverable EEPROM contents.
   Add flash page size supporting.
"""

__version__ = 'v1.0.0'

__help__ = ('\n\rmemcfg_converter  %s\n\r%s%s'
            % (__version__, __description__, __usage__))

# add pylib directory into search path
import sys
import os
pylib_dir = os.environ.get('PYLIB_BASE')
sys.path.append(pylib_dir)

# #############################################################################
#  Porting Part
# #############################################################################

import ctypes
import struct
import collections
from common import converter
from common import memmap


def generate_memcfg(memcfg_buf, memcfg_start, page_lma, vma, default):
    'generate memcfg information'

    if page_lma is None:
        raise StandardError('No page LMA!')

    if page_lma.type != page_lma.LMA_TYPE_ROM:
        # only generate ROM mempage information
        return

    if vma.label != vma.LABEL_I2C:
        # unsupported memmap
        return

    if vma.type != vma.TYPE_UNIT:
        # only generate memmap unit information
        return

    # generate memcfg information into buffer
    memcfg_start = (page_lma.start + (vma.offset&0x7F) - memcfg_start)
    for i in range(vma.len):
        memcfg_buf[memcfg_start+i] = default[i]


def getMempageInfo(map):
    'get mempage information'

    # get total page list
    virtual_pages = collections.OrderedDict()
    ram_pages     = collections.OrderedDict()
    rom_pages     = collections.OrderedDict()
    for s_name in map.GetTotalMemoryList():
        mem_info = map.GetMemoryInformation(s_name)
        if 'lma' not in mem_info:
            # non-page
            continue

        lma = mem_info['lma']
        if lma.type == lma.LMA_TYPE_VIRTUAL:
            virtual_pages[s_name] = mem_info
        elif lma.type == lma.LMA_TYPE_RAM:
            ram_pages[s_name] = mem_info
        elif lma.type == lma.LMA_TYPE_ROM:
            rom_pages[s_name] = mem_info
        else:
            raise Exception('Invalid page "%s"!' % s_name)

    # sort page list, based on address
    virtual_pages = collections.OrderedDict(sorted(virtual_pages.items(), key=lambda t: t[0]))
    ram_pages     = collections.OrderedDict(sorted(ram_pages.items(),     key=lambda t: t[0]))
    rom_pages     = collections.OrderedDict(sorted(rom_pages.items(),     key=lambda t: t[0]))

    return (virtual_pages, ram_pages, rom_pages)


def getMemcfgBuf(map, pad_to, pad_val, page_size):
    'get memcfg buffer'

    # get mempage related information
    (virtual_pages, ram_pages, rom_pages) = getMempageInfo(map)

    # get ROM page start/end address
    memcfg_start = 0xFFFFFFFF
    memcfg_end   = 0x00000000
    for s_name in rom_pages.keys():
        page_start = rom_pages[s_name]['lma'].start
        page_end   = rom_pages[s_name]['lma'].end
        if memcfg_start > page_start:
            memcfg_start = page_start
        if memcfg_end < page_end:
            memcfg_end = page_end

    # calculate memcfg buffer size
    buf_len = memcfg_end - memcfg_start + 1
    buf_len = ((buf_len + pad_to - 1) / pad_to) * pad_to
    buf_len = ((buf_len + page_size - 1) / page_size) * page_size

    # create memcfg buffer, and init to pad_val
    memcfg_buf = (ctypes.c_ubyte * buf_len)()
    for i in range(len(memcfg_buf)):
        memcfg_buf[i] = pad_val

    # walk-through entire memmap, to fill the memcfg buffer
    page_lma = None
    for s_name in map.GetTotalMemoryList():
        mem_info = map.GetMemoryInformation(s_name)
        if 'lma' in mem_info:
            # page
            page_lma = mem_info['lma']
        else:
            # memory
            vma     = mem_info['vma']
            default = mem_info['default']
            generate_memcfg(memcfg_buf, memcfg_start, page_lma, vma, default)

    # force reset last byte for each flash page to 0xFE,
    #  to indicate all flash page contents are ready,
    #  to support recoverable EEPROM contents.
    for i in range(0,len(memcfg_buf),page_size):
        memcfg_buf[i+page_size-1] = 0xFE

    # return memcfg buffer
    return memcfg_buf


def main():

    # parameter parse
    s_input  = None
    s_output = None
    s_pad_to  = '1'
    s_pad_val = '0xFF'
    s_page_size = '0x200'
    for arg in sys.argv[1:]:
        if arg.startswith('/?') or arg.startswith('--help'):
            raise StandardError(__help__)
        if arg.startswith('--input='):
            s_input = arg[8:]
        elif arg.startswith('--output='):
            s_output = arg[9:]
        elif arg.startswith('--pad-to='):
            s_pad_to = arg[9:]
        elif arg.startswith('--pad-val='):
            s_pad_val = arg[10:]
        elif arg.startswith('--page-size='):
            s_page_size = arg[12:]
        else:
            raise StandardError('Unknown argument: %s' % arg)
    if not (s_input and s_output):
        raise StandardError(__help__)

    # parameter checking
    if not (os.path.exists(s_input) and os.path.isfile(s_input)):
        raise StandardError('Invalid input file: "%s"' % s_input)
    try:
        pad_to = converter.ToInt(s_pad_to)
        if pad_to == 0:
            pad_to = 1
    except:
        raise StandardError('Invalid pad_to value: "%s"' % s_pad_to)
    try:
        pad_val = converter.ToInt(s_pad_val)
    except:
        raise StandardError('Invalid pad_val value: "%s"' % s_pad_val)
    try:
        page_size = converter.ToInt(s_page_size)
    except:
        raise StandardError('Invalid page_size value: "%s"' % s_page_size)

    # parse memmap file
    map = memmap.parse(s_input)

    # get memcfg buffer
    memcfg_buf = getMemcfgBuf(map, pad_to, pad_val, page_size)

    # create and flush buffer to output file
    try:
        file_out = open(s_output, 'wb')
    except:
        raise StandardError('Create output file failed: "%s"' % s_output)
    for i in range(len(memcfg_buf)):
        file_out.write(struct.pack('=B', memcfg_buf[i]))
    file_out.close()


# script start from here
if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\n(Exit)')
    except Exception, e:
        print('%s' % e.message),
        import traceback
        print '\n\n', traceback.format_exc()
