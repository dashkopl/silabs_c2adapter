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
 * DESCRIPTPCAN:
 *   PCA driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_PCA_H
#define __DRV_PCA_H


#if DRV_PCA_SUPPORT

/* PCA supported modes */
#define PCA_MODE_DISABLE            0x00    /* disabled */
#define PCA_MODE_CAPTURE_POS_EDGE   0x20    /* capture triggerred by positive edge on CEXn */
#define PCA_MODE_CAPTURE_NEG_EDGE   0x10    /* capture triggerred by negative edge on CEXn */
#define PCA_MODE_CAPTURE_BOTH_EDGE  0x30    /* capture triggerred by transition on CEXn */
#define PCA_MODE_SW_TIMER           0x48    /* software timer */
#define PCA_MODE_HIGH_SPEED_OUT     0x4C    /* high speed output */
#define PCA_MODE_FREQ_OUT           0x46    /* frequency output */
#define PCA_MODE_PWM_8BIT           0x42    /*  8-bit PWM */
#define PCA_MODE_PWM_16BIT          0xC2    /* 16-bit PWM */

/* PCA supported source clock */
#define PCA_CLK_CORE_CLOCK_DIV_12   0x0     /* system clock deviced by 12 */
#define PCA_CLK_CORE_CLOCK_DIV_4    0x1     /* system clock deviced by 4  */
#define PCA_CLK_T0_OVERFLOW         0x2     /* timer 0 overflow */
#define PCA_CLK_H2L_ECI             0x3     /* high-to-low transitions on ECI */
#define PCA_CLK_CORE_CLOCK          0x4     /* system clock */
#define PCA_CLK_EXT_CLOCK_DIV_8     0x5     /* external clock divided by 8 */

/* the real PCA definition is in the auto-generated file */
#define DECLARE_PCA(_name,_ch,_io,_mode,_init,_desc)    /* empty */
#define _PCA(_ch)                                       /* empty */
#include "~cfg_hw_def.h"
#undef _PCA
#undef DECLARE_PCA

#define PCA(_name)                  _name
#define _PCA_CH(_name)              COMBINE(PCA_CH_,      _name)
#define _PCA_IO(_name)              COMBINE(PCA_IO_,      _name)
#define _PCA_MODE(_name)            COMBINE(PCA_MODE_,    _name)
#define _PCA_INIT(_name)            COMBINE(PCA_INIT_,    _name)
#define _PCA_DESC(_name)            COMBINE(PCA_DESC_,    _name)
#define _PCA_PCA0CPM(_name)         COMBINE(PCA_PCA0CPM_, _name)
#define _PCA_PCA0CPL(_name)         COMBINE(PCA_PCA0CPL_, _name)
#define _PCA_PCA0CPH(_name)         COMBINE(PCA_PCA0CPH_, _name)

/******************************************************************************
 * FUNCTPCAN NAME:
 *   DRV_PCA_SetMode
 * DESCRIPTPCAN:
 *   Set PCA channel mode.
 * PARAMETERS:
 *   _name: PCA channel name.
 *   _mode: PCA channel mode.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_PCA_SetMode(_name,_mode)   do { _PCA_PCA0CPM(_name) = (_mode); } while (0)

/******************************************************************************
 * FUNCTPCAN NAME:
 *   DRV_PCA_Read
 * DESCRIPTPCAN:
 *   Read PCA channel data.
 * PARAMETERS:
 *   _name: PCA channel name.
 * RETURN:
 *   PCA channel data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_PCA_Read(_name)         (((_PCA_MODE(_name)==PCA_MODE_FREQ_OUT) ||  \
                                     (_PCA_MODE(_name)==PCA_MODE_PWM_8BIT)) ?   \
                                     _PCA_PCA0CPH(_name) :                      \
                                     (((UINT16)_PCA_PCA0CPH(_name)<<8) |        \
                                      (_PCA_PCA0CPL(_name)<<0)))

/******************************************************************************
 * FUNCTPCAN NAME:
 *   DRV_PCA_Write
 * DESCRIPTPCAN:
 *   Write PCA channel data.
 * PARAMETERS:
 *   _name: PCA channel name.
 *   _val : PCA channel value.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_PCA_Write(_name,_val)   do {                                                \
                                        if ((_PCA_MODE(_name) == PCA_MODE_FREQ_OUT) ||  \
                                            (_PCA_MODE(_name) == PCA_MODE_PWM_8BIT))    \
                                        {                                               \
                                            _PCA_PCA0CPH(_name) = (UINT8)(_val);        \
                                        }                                               \
                                        else                                            \
                                        {                                               \
                                            _PCA_PCA0CPL(_name) = (UINT8)((_val)>>0);   \
                                            _PCA_PCA0CPH(_name) = (UINT8)((_val)>>8);   \
                                        }                                               \
                                    } while (0)

/******************************************************************************
 * FUNCTPCAN NAME:
 *   DRV_PCA_Init
 * DESCRIPTPCAN:
 *   PCA init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_PCA_Init(void);

#endif


#endif /* __DRV_PCA_H */

