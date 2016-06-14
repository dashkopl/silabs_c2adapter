__copyright__ = """
COPYRIGHT:
 Copyright (c) 2016      CreaLights Inc.      All rights reserved.

 This is unpublished proprietary source code of CreaLights Inc.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.
"""

__description__ = """
DESCRIPTION:
 A script used to convert the hardware definitions. (C8051Fxxx)
"""

__usage__ = """
USAGE:
 hw_converter <options>

 <options> definition:
  --input=<path> : Input hardware definition file path;
  --output=<path>: Output hardware definition C header path;
"""

__history__ = """
HISTORY:
 v1.0.0        2016/4/27        Panda.Xiong
   Initially created.
"""

__version__ = 'v1.0.0'

__help__ = ('\n\rhw_converter  %s\n\r%s%s'
            % (__version__, __description__, __usage__))

# add pylib directory into search path
import sys
import os
pylib_dir = os.environ.get('PYLIB_BASE')
sys.path.append(pylib_dir)

# #############################################################################
#  Porting Part
# #############################################################################

import re
from common import converter


def _def(f_out, name, sub_name, value):
    ss = '%s_%s' % (sub_name, name)
    f_out.write('#define %-40s %s\n' % (ss, value))


def _def_io(f_out, s_def):
    # /* name            bit         mode         init  desc */
    # (ADC_VREF_OUT,  _IO(P0.0), IO_MODE_ANALOG,  HIGH,  "")

    s_regex = r'^\(([^,]+),\s*_IO\(P([A-Z,a-z,0-9]+)\.([A-Z,a-z,0-9]+)\),\s*([^,]+),\s*([^,]+),\s*("[^"]*")\)'
    p = re.compile(s_regex)
    result = p.split(s_def)[1:-1]

    if not result:
        raise Exception('IO: parsing failed for "%s"' % s_def)

    (name, port, bit, mode, init, desc) = result

    s_io = 'P%s_%s' % (port, bit)
    f_out.write('\n/* IO: %s */\n' % name)
    if converter.ToInt(port) < 4:
        f_out.write('SBIT(%s, P%s, %s);\n' % (name, port, bit))
    else:
        f_out.write('SBIT(%s, P%s, %s); /* pseudo definition, to pass compiling */ \n' % (name, 0, 0))
    _def(f_out, name, 'IO_PORT', port)
    _def(f_out, name, 'IO_BIT',  bit)
    _def(f_out, name, 'IO_MODE', mode)
    _def(f_out, name, 'IO_INIT', init)
    _def(f_out, name, 'IO_DESC', desc)
    _def(f_out, name, 'IO_MASK', 'P%sMASK'%port)
    _def(f_out, name, 'IO_MAT',  'P%sMAT'%port)
    _def(f_out, name, 'IO_MDIN', 'P%sMDIN'%port)
    _def(f_out, name, 'IO_MDOUT','P%sMDOUT'%port)
    _def(f_out, name, 'IO_SKIP', 'P%sSKIP'%port)
    _def(f_out, s_io, 'IO_INIT',  init)
    _def(f_out, s_io, 'IO_MODE',  mode)


def _def_vdac(f_out, s_def):
    # /*   name          channel      mode              init   desc */
    # (VDAC_Reserved_0,  _VDAC(0),  VDAC_MODE_DISABLE, 0x0000,  "")

    s_regex = r'^\(([^,]+),\s*_VDAC\(([A-Z,a-z,0-9]+)\),\s*([^,]+),\s*([^,]+),\s*("[^"]*")\)'
    p = re.compile(s_regex)
    result = p.split(s_def)[1:-1]

    if not result:
        raise Exception('VDAC: parsing failed for "%s"' % s_def)

    (name, channel, mode, init, desc) = result

    f_out.write('\n/* VDAC: %s */\n' % (name))
    _def(f_out, name, 'VDAC_CH',   channel)
    _def(f_out, name, 'VDAC_MODE', mode)
    _def(f_out, name, 'VDAC_INIT', init)
    _def(f_out, name, 'VDAC_DESC', desc)
    f_out.write('\n')


def _def_idac(f_out, s_def):
    # /*   name          channel      mode               init   desc */
    # (IDAC_Reserved_0,  _IDAC(0),  IDAC_MODE_DISABLE,  0x0000,  "")

    s_regex = r'^\(([^,]+),\s*_IDAC\(([A-Z,a-z,0-9]+)\),\s*([^,]+),\s*([^,]+),\s*("[^"]*")\)'
    p = re.compile(s_regex)
    result = p.split(s_def)[1:-1]

    if not result:
        raise Exception('IDAC: parsing failed for "%s"' % s_def)

    (name, channel, mode, init, desc) = result

    f_out.write('\n/* IDAC: %s */\n' % (name))
    _def(f_out, name, 'IDAC_CH',   channel)
    _def(f_out, name, 'IDAC_MODE', mode)
    _def(f_out, name, 'IDAC_INIT', init)
    _def(f_out, name, 'IDAC_DESC', desc)
    f_out.write('\n')


def _def_pca(f_out, s_def):
    # /*   name          ch          io               mode           init   desc  */
    # (PCA_Reserved_1, _PCA(1),  IO_Reserved_P2_7, PCA_MODE_DISABLE, 0xFF,   "")

    s_regex = r'^\(([^,]+),\s*_PCA\(([A-Z,a-z,0-9]+)\),\s*([^,]+),\s*([^,]+),\s*([^,]+),\s*("[^"]*")\)'
    p = re.compile(s_regex)
    result = p.split(s_def)[1:-1]

    if not result:
        raise Exception('PCA: parsing failed for "%s"' % s_def)

    (name, channel, io, mode, init, desc) = result

    f_out.write('\n/* PCA: %s */\n' % (name))
    _def(f_out, name, 'PCA_CH',   channel)
    _def(f_out, name, 'PCA_IO',   io)
    _def(f_out, name, 'PCA_MODE', mode)
    _def(f_out, name, 'PCA_INIT', init)
    _def(f_out, name, 'PCA_DESC', desc)
    _def(f_out, name, 'PCA_PCA0CPM', 'PCA0CPM%s'%channel)
    _def(f_out, name, 'PCA_PCA0CPL', 'PCA0CPL%s'%channel)
    _def(f_out, name, 'PCA_PCA0CPH', 'PCA0CPH%s'%channel)
    f_out.write('\n')


def generate_hw(f_in, f_out):
    line = 0
    for s_line in f_in:
        line += 1
        s_line.strip()

        try:
            if   s_line[0:11] == 'DECLARE_IO(':
                _def_io(f_out, s_line[10:])
            elif s_line[0:13] == 'DECLARE_VDAC(':
                _def_vdac(f_out, s_line[12:])
            elif s_line[0:13] == 'DECLARE_IDAC(':
                _def_idac(f_out, s_line[12:])
            elif s_line[0:12] == 'DECLARE_PCA(':
                _def_pca(f_out, s_line[11:])
            else:
                pass
        # except Exception, e:
        #     print('%s' % e.message),
        #     import traceback
        #     print '\n\n', traceback.format_exc()
        except:
            raise Exception('Parsing failed at line %d' % line)


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
    f_in  = file(s_input, 'r')

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

    # generate hardware inforation
    generate_hw(f_in, f_out)

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
