/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016      CreaLights Inc.      All rights reserved.
 *
 *   This is unpublished proprietary source code of CreaLights Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * DESCRIPTION:
 *   UART driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_UART_H
#define __DRV_UART_H


#if DRV_UART_SUPPORT

#define DRV_UART_IsRxEmpty()        (!RI0)
#define DRV_UART_ReadByte()         (RI0=0, SBUF0)
#define DRV_UART_WriteByte(_vByte)  do { TI0=0; SBUF0=(UINT8)(_vByte); } while (0)
#define DRV_UART_IsTxEmpty()        (!TI0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_UART_Init
 * DESCRIPTION:
 *   UART init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_UART_Init()                                                     \
    do {                                                                    \
        /* timer 1:                                                         \
         *  clock source: system clock;                                     \
         *  mode: 8-bit auto-reload;                                        \
         *  gate: controlled by TR1;                                        \
         */                                                                 \
        SET_BIT(CKCON,3);                                                   \
        TMOD = (TMOD&0x0F) | (0x2<<4);                                      \
        TH1  = (256 - (CORE_CLOCK*10/2/DRV_UART_BAUDRATE+5)/10);            \
        TR1  = 1; /* enable timer 1 */                                      \
                                                                            \
        /* force no-skip UART_TXD/RXD, and enable UART at cross-bar */      \
        drv_io_SetSkip(UART_TXD, DISABLE);                                  \
        drv_io_SetSkip(UART_RXD, DISABLE);                                  \
        XBR0 |= (1<<0);                                                     \
                                                                            \
        /* UART:                                                            \
         *  8-bit mode;                                                     \
         *  receive enabled/disabled;                                       \
         *  set TI0=1, to indicate UART TX is ready;                        \
         */                                                                 \
        SCON0 = (((DRV_UART_RX_ENABLE&0x1)<<4) | (1<<1));                   \
    } while (0)

#endif


#endif /* __DRV_UART_H */

