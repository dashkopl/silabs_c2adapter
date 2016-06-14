__copyright__ = """
COPYRIGHT:
 Copyright (c) 2016      CreaLights Inc.      All rights reserved.

 This is unpublished proprietary source code of CreaLights Inc.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.
"""

__description__ = """
DESCRIPTION:
 A tool to convert memmap excel file to mempage C header file.
"""

__usage__ = """
USAGE:
 mempage_converter <options>

 <options> definition:
  --input=<path> : Input memmap file path;
  --output=<path>: Output mempage C header path;
"""

__history__ = """
HISTORY:
 v1.0.0        2016/2/19        Panda.Xiong
   Initially created.
"""

__version__ = 'v1.0.0'

__help__ = ('\n\rmempage_converter  %s\n\r%s%s'
            % (__version__, __description__, __usage__))

# add pylib directory into search path
import sys
import os
pylib_dir = os.environ.get('PYLIB_BASE')
sys.path.append(pylib_dir)

# #############################################################################
#  Porting Part
# #############################################################################

import collections
from ctypes import *
from common import memmap


I2C_ADDR      = 0xFE
RAM_PAGE_SIZE = 0x20
ROM_PAGE_SIZE = 0x80


def _def_mempage(f_out, s_type, vma, s_val, s_name):
    'define mempage'

    if vma.label != vma.LABEL_I2C:
        # unsupported page
        return

    if vma.page_type == vma.PAGE_TYPE_DIRECT:
        page_name = 'MEMPAGE_%s_DIRECT_%02X_%02X' % (s_type, vma.addr, vma.offset)
    else:
        page_name = 'MEMPAGE_%s_EXTEND_%02X_%02X' % (s_type, vma.addr, vma.page)

    f_out.write('#define %-40s %-8s /* %s */\n' % (page_name, s_val, s_name))


def _def_pwd(f_out, is_read, pwd):
    'define password'

    if is_read:
        level = pwd.read_level
    else:
        level = pwd.write_level

    if level == pwd.PWD_LEVEL_NORMAL:
        s_pwd = 'CFG_PWD_LEVEL_NORMAL,'
    elif level == pwd.PWD_LEVEL_UserRO:
        s_pwd = 'CFG_PWD_LEVEL_UserRO,'
    elif level == pwd.PWD_LEVEL_UserRW:
        s_pwd = 'CFG_PWD_LEVEL_UserRW,'
    elif level == pwd.PWD_LEVEL_OEM:
        s_pwd = 'CFG_PWD_LEVEL_OEM,'
    elif level == pwd.PWD_LEVEL_FACTORY:
        s_pwd = 'CFG_PWD_LEVEL_FACTORY,'
    else:
        s_pwd = 'CFG_PWD_LEVEL_ROOT,'

    f_out.write('    %-30s               \\\n' % s_pwd)


def generate_pid(f_out, virtual_pages, ram_pages, rom_pages):
    'generate page id information'

    page_pid = 0

    f_out.write('/* Page PID (Page Virtual ID) */\n')
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_PID_INVALID', -1))

    # output mempage definitions: VIRTUAL
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_VIRTUAL_PAGES_HEAD', page_pid))
    for s_name in virtual_pages.keys():
        _def_mempage(f_out, 'PID', virtual_pages[s_name]['vma'], ('%d'%page_pid), s_name)
        page_pid += 1
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_VIRTUAL_PAGES_TAIL', page_pid-1))
    f_out.write('#define %-40s %s\n' % ('MEMPAGE_VIRTUAL_PAGES_COUNT', '((MEMPAGE_VIRTUAL_PAGES_TAIL - MEMPAGE_VIRTUAL_PAGES_HEAD) + 1)'))

    # output mempage definitions: RAM
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_RAM_PAGES_HEAD', page_pid))
    for s_name in ram_pages.keys():
        _def_mempage(f_out, 'PID', ram_pages[s_name]['vma'], ('%d'%page_pid), s_name)
        page_pid += 1
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_RAM_PAGES_TAIL', page_pid-1))
    for s_name in ram_pages.keys():
        f_out.write('#define %-40s 0x%04X\n' % ('MEMPAGE_RAM_PAGES_BASE', ram_pages[s_name]['lma'].start))
        f_out.write('#define %-40s %s\n' % ('MEMPAGE_RAM_PAGES_COUNT', '((MEMPAGE_RAM_PAGES_TAIL - MEMPAGE_RAM_PAGES_HEAD) + 1)'))
        break

    # output mempage definitions: ROM
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_ROM_PAGES_HEAD', page_pid))
    for s_name in rom_pages.keys():
        _def_mempage(f_out, 'PID', rom_pages[s_name]['vma'], ('%d'%page_pid), s_name)
        page_pid += 1
    f_out.write('#define %-40s %d\n' % ('MEMPAGE_ROM_PAGES_TAIL', page_pid-1))
    for s_name in rom_pages.keys():
        f_out.write('#define %-40s 0x%04X\n' % ('MEMPAGE_ROM_PAGES_BASE', rom_pages[s_name]['lma'].start))
        f_out.write('#define %-40s %s\n' % ('MEMPAGE_ROM_PAGES_COUNT', '((MEMPAGE_ROM_PAGES_TAIL - MEMPAGE_ROM_PAGES_HEAD) + 1)'))
        break


def generate_lma(f_out, virtual_pages, ram_pages, rom_pages):
    'generate page LMA information'

    f_out.write('/* Page LMA (Logical-Memory-Address) */\n')

    # output mempage definitions: VIRTUAL
    # no LMA for VIRTUAL page

    # output mempage definitions: RAM
    page_pid = 0
    for s_name in ram_pages.keys():
        lma_base = ram_pages[s_name]['lma'].start
        break
    for s_name in ram_pages.keys():
        s_lma = '0x%04X' % (lma_base+page_pid*RAM_PAGE_SIZE)
        _def_mempage(f_out, 'LMA', ram_pages[s_name]['vma'], s_lma, s_name)
        page_pid += 1

    # output mempage definitions: ROM
    page_pid = 0
    for s_name in rom_pages.keys():
        lma_base = rom_pages[s_name]['lma'].start
        break
    for s_name in rom_pages.keys():
        s_lma = '0x%04X' % (lma_base+page_pid*ROM_PAGE_SIZE)
        _def_mempage(f_out, 'LMA', rom_pages[s_name]['vma'], s_lma, s_name)
        page_pid += 1


def generate_pwd(f_out, virtual_pages, ram_pages, rom_pages):
    'generate password information'

    f_out.write('/* Page Read/Write Password Level */\n')

    # output page read password level information
    f_out.write('#define MEMPAGE_READ_PWD_LEVEL_TABLE             \\\n')
    f_out.write('{                                                \\\n')
    for s_name in virtual_pages.keys():
        _def_pwd(f_out, True, virtual_pages[s_name]['password'])
    for s_name in ram_pages.keys():
        _def_pwd(f_out, True, ram_pages[s_name]['password'])
    for s_name in rom_pages.keys():
        _def_pwd(f_out, True, rom_pages[s_name]['password'])
    f_out.write('}\n')

    # output page write password level information
    f_out.write('#define MEMPAGE_WRITE_PWD_LEVEL_TABLE            \\\n')
    f_out.write('{                                                \\\n')
    for s_name in virtual_pages.keys():
        _def_pwd(f_out, False, virtual_pages[s_name]['password'])
    for s_name in ram_pages.keys():
        _def_pwd(f_out, False, ram_pages[s_name]['password'])
    for s_name in rom_pages.keys():
        _def_pwd(f_out, False, rom_pages[s_name]['password'])
    f_out.write('}\n')


def Generate_mempage(f_out, map):
    'generate mempage information'

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

    # generate page id information
    f_out.write('\n')
    generate_pid(f_out, virtual_pages, ram_pages, rom_pages)
    f_out.write('\n')

    # generate page LMA information
    f_out.write('\n')
    generate_lma(f_out, virtual_pages, ram_pages, rom_pages)
    f_out.write('\n')

    # generate password information
    f_out.write('\n')
    generate_pwd(f_out, virtual_pages, ram_pages, rom_pages)
    f_out.write('\n')


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
    f_out.write('#define %s\n\n' % sFileName)

    # generate mempage inforation
    Generate_mempage(f_out, map)

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
