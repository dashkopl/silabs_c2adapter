/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016    PANDA(yaxi1984@gmail.com)    All rights reserved.
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA 02111-1307 USA
 *
 * DESCRIPTION:
 *   GPIO driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_IO_H
#define __DRV_IO_H


#if DRV_IO_SUPPORT

#define IO_MODE_ANALOG      0x0 /* analog              */
#define IO_MODE_DIGITAL_OD  0x2 /* digital, open-drain */
#define IO_MODE_DIGITAL_PP  0x3 /* digital, push-pull  */

/* the real IO definition is in the auto-generated file */
#define DECLARE_IO(_name,_bit,_mode,_init,_desc)    /* empty */
#define _IO(_port,_bit)                             /* empty */
#include "~cfg_hw_def.h"
#undef _IO
#undef DECLARE_IO

#define IO_PORT_MAX         3
#define IO_BIT_MAX          7

#define IO(_name)           _name
#define _IO_PORT(_name)     COMBINE(IO_PORT_, _name)
#define _IO_BIT(_name)      COMBINE(IO_BIT_,  _name)
#define _IO_MODE(_name)     COMBINE(IO_MODE_, _name)
#define _IO_INIT(_name)     COMBINE(IO_INIT_, _name)
#define _IO_DESC(_name)     COMBINE(IO_DESC_, _name)
#define _IO_MASK(_name)     COMBINE(IO_MASK_, _name)
#define _IO_MAT(_name)      COMBINE(IO_MAT_,  _name)
#define _IO_MDIN(_name)     COMBINE(IO_MDIN_, _name)
#define _IO_MDOUT(_name)    COMBINE(IO_MDOUT_,_name)
#define _IO_SKIP(_name)     COMBINE(IO_SKIP_, _name)
#define _PIN_MODE(_bit)     COMBINE(IO_MODE_, _bit)
#define _PIN_INIT(_bit)     COMBINE(IO_INIT_, _bit)

#define _PORT_MDIN(_port)   ( ((((UINT8)_PIN_MODE(COMBINE(_port,_0))>>1)&0x1) << 0)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_1))>>1)&0x1) << 1)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_2))>>1)&0x1) << 2)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_3))>>1)&0x1) << 3)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_4))>>1)&0x1) << 4)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_5))>>1)&0x1) << 5)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_6))>>1)&0x1) << 6)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_7))>>1)&0x1) << 7) )
#define _PORT_MDOUT(_port)  ( ((((UINT8)_PIN_MODE(COMBINE(_port,_0))>>0)&0x1) << 0)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_1))>>0)&0x1) << 1)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_2))>>0)&0x1) << 2)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_3))>>0)&0x1) << 3)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_4))>>0)&0x1) << 4)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_5))>>0)&0x1) << 5)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_6))>>0)&0x1) << 6)     \
                            | ((((UINT8)_PIN_MODE(COMBINE(_port,_7))>>0)&0x1) << 7) )
#define _PORT_INIT(_port)   ( ((UINT8)_PIN_INIT(COMBINE(_port,_0)) << 0)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_1)) << 1)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_2)) << 2)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_3)) << 3)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_4)) << 4)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_5)) << 5)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_6)) << 6)                \
                            | ((UINT8)_PIN_INIT(COMBINE(_port,_7)) << 7) )

/* IO low-level API */
#define drv_io_Read(_port,_bit)     READ_BIT(_port, _bit)
#define drv_io_Write(_port,_bit,_v) WRITE_BIT(_port, _bit, (_v))
#define drv_io_Toggle(_port,_bit)   REVERSE_BIT(_port, _bit)
#define drv_io_SetAnalog(_name)     CLR_BIT(_IO_MDIN(_name),  _IO_BIT(_name))
#define drv_io_SetDigital(_name)    SET_BIT(_IO_MDIN(_name),  _IO_BIT(_name))
#define drv_io_SetOutputOD(_name)   CLR_BIT(_IO_MDOUT(_name), _IO_BIT(_name))
#define drv_io_SetOutputPP(_name)   SET_BIT(_IO_MDOUT(_name), _IO_BIT(_name))
#define drv_io_SetSkip(_name,_en)   WRITE_BIT(_IO_SKIP(_name),_IO_BIT(_name), (_en))
#define drv_io_SetMode(_name,_mode) do {                                    \
                                        switch (_mode)                      \
                                        {                                   \
                                            default:                        \
                                            case IO_MODE_ANALOG:            \
                                                drv_io_SetAnalog(_name);    \
                                                drv_io_SetOutputOD(_name);  \
                                                break;                      \
                                            case IO_MODE_DIGITAL_OD:        \
                                                drv_io_SetDigital(_name);   \
                                                drv_io_SetOutputOD(_name);  \
                                                break;                      \
                                            case IO_MODE_DIGITAL_PP:        \
                                                drv_io_SetDigital(_name);   \
                                                drv_io_SetOutputPP(_name);  \
                                                break;                      \
                                        }                                   \
                                    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_SetMode
 * DESCRIPTION:
 *   Set IO pin mode.
 * PARAMETERS:
 *   _pin : IO pin.
 *   _mode: IO mode.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_IO_SetMode(_pin, _mode) drv_io_SetMode(_pin, _mode)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_Read
 * DESCRIPTION:
 *   Read IO pin input data.
 * PARAMETERS:
 *   _pin : IO pin.
 * RETURN:
 *   HIGH/LOW: IO pin input data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_IO_Read(_pin)           (_pin)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_Write
 * DESCRIPTION:
 *   Write IO pin output data.
 * PARAMETERS:
 *   _pin : IO pin.
 *   _val : =HIGH, output high.
 *          =LOW,  output low.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_IO_Write(_pin, _val)    do { (_pin) = (_val); } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_Toggle
 * DESCRIPTION:
 *   Toggle IO pin output data.
 * PARAMETERS:
 *   _pin : IO pin.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_IO_Toggle(_pin)         drv_io_Toggle(COMBINE(P,_IO_PORT(_pin)),    \
                                                  _IO_BIT(_pin))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_Init
 * DESCRIPTION:
 *   IO Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_IO_Init(void);

#endif


#endif /* __DRV_IO_H */

