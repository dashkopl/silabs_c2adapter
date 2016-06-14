/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016      CreaLights Inc.      All rights reserved.
 *
 *   This is unpublished proprietary source code of CreaLights Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * DESCRIPTPCAN:
 *   PCA driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_PCA_SUPPORT

/******************************************************************************
 * FUNCTPCAN NAME:
 *   DRV_PCA_Init
 * DESCRIPTPCAN:
 *   PCA Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_PCA_Init(void)
{
    UINT8   vPCA0ME = 0x00;

    /* PCA channel init */
  #define DECLARE_PCA(_name,_ch,_io,_mode,_init,_desc)                      \
    do {                                                                    \
        DRV_PCA_Write(_name, _init);                                        \
        DRV_PCA_SetMode(_name, _mode);                                      \
                                                                            \
        if (_mode != PCA_MODE_DISABLE)                                      \
        {                                                                   \
            /* force no-skip this PCA channel for GPIO */                   \
            drv_io_SetSkip(_PCA_IO(_name), DISABLE);                        \
            vPCA0ME++;                                                      \
        }                                                                   \
    } while (0);
  #include "cfg_hw_def.h"
  #undef DECLARE_PCA

    /* init PCA0:
     *  reset PCA counter;
     *  PCA clock source: defined by DRV_PCA_SOURCE_CLOCK;
     *  enable PCA;
     */
    PCA0H  = 0x00;
    PCA0L  = 0x00;
    PCA0MD = (DRV_PCA_SOURCE_CLOCK<<1);
    PCA0CN = 0x40;

    /* enable CEXn at cross-bar */
    XBR1 |= (vPCA0ME&0x7);
}

#endif

