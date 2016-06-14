__copyright__ = """
COPYRIGHT:
 Copyright (c) 2016      CreaLights Inc.      All rights reserved.

 This is unpublished proprietary source code of CreaLights Inc.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.
"""

__description__ = """
DESCRIPTION:
 A tool to convert memmap excel file to memmap C header file.
"""

__usage__ = """
USAGE:
 memmap_converter <options>

 <options> definition:
  --input=<path> : Input memmap excel file path;
  --output=<path>: Output memmap C header path;
"""

__history__ = """
HISTORY:
 v1.0.0        2016/2/19        Panda.Xiong
   Initially created.
"""

__version__ = 'v1.0.0'

__help__ = ('\n\rmemmap_converter  %s\n\r%s%s'
            % (__version__, __description__, __usage__))

# add pylib directory into search path
import sys
import os
pylib_dir = os.environ.get('PYLIB_BASE')
sys.path.append(pylib_dir)

# #############################################################################
#  Porting Part
# #############################################################################

from ctypes import *
from common import memmap


I2C_ADDR      = 0xFE
RAM_PAGE_SIZE = 0x20
ROM_PAGE_SIZE = 0x80


def _def(f_out, name, sub_name, value):
    ss = 'MEMMAP_%s_%s' % (sub_name, name)
    f_out.write('#define %-60s %s\n' % (ss, value))


def _def_memmap(f_out, name, vma, page_lma):
    'define memmap'

    if page_lma is None:
        raise StandardError('No page LMA for memory "%s"!' % name)

    if vma.label != vma.LABEL_I2C:
        # unsupported memmap
        return

    offset_mask = ROM_PAGE_SIZE-1
    if vma.page_type == vma.PAGE_TYPE_DIRECT:
        page_name = 'MEMPAGE_PID_DIRECT_%02X_%02X' % (vma.addr, vma.page)
    else:
        page_name = 'MEMPAGE_PID_EXTEND_%02X_%02X' % (vma.addr, vma.page)

    # remap page
    if ((page_name == ('MEMPAGE_PID_DIRECT_%.2X_00'%I2C_ADDR))
            and (vma.offset >= ROM_PAGE_SIZE-RAM_PAGE_SIZE)):
        page_name   = 'MEMPAGE_PID_DIRECT_%.2X_%.2X' % (I2C_ADDR, ROM_PAGE_SIZE-RAM_PAGE_SIZE)
        offset_mask = RAM_PAGE_SIZE-1

    if vma.type == vma.TYPE_UNIT:
        # memory unit
        _def(f_out, name, 'TYPE',    'MEMMAP_TYPE_UNIT')
    else:
        # memory bit
        _def(f_out, name, 'TYPE',    'MEMMAP_TYPE_BIT')

    # _def(f_out, name, 'PAGE',        page_name)
    _def(f_out, name, 'ADDR',        '0x%02X' % vma.addr)
    _def(f_out, name, 'OFFSET',      '0x%02X' % (vma.offset&offset_mask))
    _def(f_out, name, 'REAL_OFFSET', '0x%02X' % vma.offset)
    if vma.bit == -1:
        _def(f_out, name, 'BIT',     '-1')
    else:
        _def(f_out, name, 'BIT',     '0x%X' % vma.bit)
    _def(f_out, name, 'LEN',         '0x%X' % vma.len)
    _def(f_out, name, 'LMA_TYPE',    '0x%X' % page_lma.type)
    _def(f_out, name, 'LMA',         '0x%X' % (page_lma.start + (vma.offset&offset_mask)))

    f_out.write('\n')


def generate_memmap(map, f_out):
    'generate memmap information'

    # output memmap definitions one by one
    page_lma = None
    for s_name in map.GetTotalMemoryList():
        mem_info = map.GetMemoryInformation(s_name)
        if 'lma' in mem_info:
            # page
            page_lma = mem_info['lma']
        else:
            # memory
            vma = mem_info['vma']
            f_out.write('/* %s */\n' % s_name)
            _def_memmap(f_out, s_name, vma, page_lma)


def main():

    # parameter parse
    s_input  = None
    s_output = None
    for arg in sys.argv[1:]:
        if arg.startswith('/?') or arg.startswith('--help'):
            raise StandardError(__help__)
        if arg.startswith('--input='):
            s_input = arg[8:]
        elif arg.startswith('--output='):
            s_output = arg[9:]
        else:
            raise StandardError('Unknown argument: %s' % arg)
    if not (s_input and s_output):
        raise StandardError(__help__)

    # parse memmap file
    map = memmap.parse(s_input)

    # open file
    f_out = file(s_output, 'w')

    # add header for output file
    sFileName = '__%s' % (os.path.basename(s_output).upper())
    sFileName = sFileName.replace('~', '_')
    sFileName = sFileName.replace('.', '_')
    sFileName = sFileName.replace('-', '_')
    sFileName = sFileName.replace('(', '_')
    sFileName = sFileName.replace(')', '_')
    sFileName = sFileName.replace(' ', '_')
    f_out.write('/* Auto created by "%s", do not modify it !!! */\n\n'
                % os.path.basename(sys.argv[0]))
    f_out.write('#ifndef %s\n' % sFileName)
    f_out.write('#define %s\n\n\n' % sFileName)

    # generate memmap inforation
    generate_memmap(map, f_out)

    # add tail for output file
    f_out.write('\n#endif /* %s */\n\n' % sFileName)
    f_out.flush()
    f_out.close()


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
