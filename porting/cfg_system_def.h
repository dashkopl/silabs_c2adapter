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
 *   System behavior definition related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_SYSTEM_DEF_H
#define __CFG_SYSTEM_DEF_H


/* basic definition related */
//#define __C8051F320__
#define __C8051F321__
#define IMAGE_TYPE                  'BOOT'      /* image type */
#define MCU_TYPE                    'F321'      /* mcu type   */

/* on-chip digital peripheral */
#define DRV_CLOCK_SUPPORT           1   /* Clock */
 #define CORE_CLOCK                 24000000UL  /* Hz */
#define DRV_RESET_SUPPORT           1   /* Reset */
#define DRV_PCA_SUPPORT             0   /* PCA */
 #define DRV_PCA_SOURCE_CLOCK       PCA_CLK_CORE_CLOCK
#define DRV_WATCHDOG_SUPPORT        (0 && DRV_PCA_SUPPORT)  /* Watchdog */
 #define DRV_WATCHDOG_TIMEOUT       3000 /* 25.6~6553.6 ms */
#define DRV_UART_SUPPORT            1   /* UART */
 #define DRV_UART_BAUDRATE          115200UL    /* bps */
 #define DRV_UART_RX_ENABLE         0
#define DRV_IO_SUPPORT              1   /* UART */
#define DRV_FLASH_SUPPORT           1   /* Flash */
#define DRV_TIMER_SUPPORT           1   /* Timer */
 #define DRV_TIMER_INTERVAL         1   /* ms */
#define DRV_USB_SUPPORT             1   /* USB Slave */
 #define DRV_USB_VID                0x10C4  /* VID */
 #define DRV_USB_PID                0xEA61  /* PID */

/* on-chip analog peripheral */
#define DRV_VREF_SUPPORT            0   /* Voltage Reference */
#define DRV_ADC_SUPPORT             (0 && DRV_VREF_SUPPORT)
 #define DRV_ADC_SAR_RATE           100 /* ksps */

/* simulated peripheral */
#define DRV_I2CM_SUPPORT            0   /* I2C Master */
 #define DRV_I2CM_RATE              400 /* 80/100/200/400 KHz */
#define DRV_MDIOM_SUPPORT           1   /* MDIO Master */
 #define DRV_MDIOM_RATE             3   /* 1/2/3/4 MHz */
#define DRV_C2M_SUPPORT             1   /* C2 Master */

/* off-chip device */
#define DEV_RETRY_MAX_TIME          2000    /* ms */
#define DEV_RETRY_INTERVAL          10      /* ms */
#define DEV_VCC_MIN                 30000   /* mV */
#define DEV_VCC_MAX                 36000   /* mV */

/* frame related (currently, only support version 1) */
#define PKT_SUPPORT                 1   /* USB packet global enable/disable */
#define PKT_MAX_LEN                 1084   /* frame maximum length */
#define PKT_MAGIC                   0x434C /* frame magic number */
#define PKT_VERSION                 0x0001 /* frame content version */
#define PKT_DEBUG_SUPPORT           (0 && PKT_SUPPORT)      /* packet debugging */
#define PKT_SYSTEM_SUPPORT          (0 && PKT_SUPPORT)      /* USB packet: System */
#define PKT_I2CM_SUPPORT            (1 && PKT_SUPPORT)      /* USB packet: I2C Master */
 #define PKT_I2CM_RATE              100 /* 80/100/200/400 KHz */
 #define PKT_I2CM_VS_SUPPORT        (1 && PKT_I2CM_SUPPORT) /* Virtual I2C Slave */
  #define PKT_I2CM_VS_ADDR          (0xFE)                  /* Virtual I2C Slave Address */
#define PKT_MDIOM_SUPPORT           (1 && PKT_SUPPORT && DRV_MDIOM_SUPPORT) /* USB packet: MDIO Master */
 #define PKT_MDIOM_RATE             4   /* 1/2/4 MHz */
#define PKT_C2M_SUPPORT             (1 && PKT_SUPPORT && DRV_C2M_SUPPORT)   /* USB packet: C2 Master */

/* other function */
#define CFG_SUPPORT                 1   /* Config Engine */


#endif /* __CFG_SYSTEM_DEF_H */

