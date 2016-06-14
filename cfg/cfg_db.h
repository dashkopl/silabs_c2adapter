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
 *   Configuration database related.
 * HISTORY:
 *   2016.2.15        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_DB_H
#define __CFG_DB_H


#if CFG_SUPPORT

#ifdef _CFG_DB_INTERNAL_
 #define _CFG_DB_EXTERNAL_  /* empty */
#else
 #define _CFG_DB_EXTERNAL_  extern
#endif

#if 1

#define I2CS_PAGE_SIZE      0x80
#define I2CS_INVALID_DATA   0xAAAAAAAAUL

/* RAM page related */
#define CFG_RAM_PAGE_SIZE   0x20
typedef UINT8   CFG_RAM_PAGE_T[CFG_RAM_PAGE_SIZE];
#ifdef _CFG_DB_INTERNAL_
 LOCATED_VARIABLE_NO_INIT(aRamPageBuf[MEMPAGE_RAM_PAGES_COUNT], CFG_RAM_PAGE_T, SEG_PDATA, MEMPAGE_RAM_PAGES_BASE);
#endif

/* ROM page related */
#define CFG_ROM_PAGE_SIZE   I2CS_PAGE_SIZE
typedef UINT8   CFG_ROM_PAGE_T[CFG_ROM_PAGE_SIZE];
#ifdef _CFG_DB_INTERNAL_
 LOCATED_VARIABLE_NO_INIT(aRomPageBuf[MEMPAGE_ROM_PAGES_COUNT], CFG_ROM_PAGE_T, SEG_CODE, MEMPAGE_ROM_PAGES_BASE);
#endif

#endif

/* config internal API */
#if 0
#define CFG_RAM_GET8(addr)      PDATA_U8(addr)
#define CFG_RAM_SET8(addr,v)    do { PDATA_U8(addr)  = (UINT8)(v);  } while (0)
#define CFG_RAM_GET16(addr)     PDATA_U16(addr)
#define CFG_RAM_SET16(addr,v)   do { PDATA_U16(addr) = (UINT16)(v); } while (0)
#define CFG_RAM_GET32(addr)     PDATA_U32(addr)
#define CFG_RAM_SET32(addr,v)   do { PDATA_U32(addr) = (UINT32)(v); } while (0)
#define CFG_ROM_GET8(addr)      CODE_U8(addr)
#define CFG_ROM_SET8(addr,v)    do { UINT8 SEG_PDATA  _v=(UINT8)(v);  EEPROM_MEMCPY((UINT16)(addr), &_v, 1); } while (0)
#define CFG_ROM_GET16(addr)     CODE_U16(addr)
#define CFG_ROM_SET16(addr,v)   do { UINT16 SEG_PDATA _v=(UINT16)(v); EEPROM_MEMCPY((UINT16)(addr), &_v, 2); } while (0)
#define CFG_ROM_GET32(addr)     CODE_U32(addr)
#define CFG_ROM_SET32(addr,v)   do { UINT32 SEG_PDATA _v=(UINT32)(v); EEPROM_MEMCPY((UINT16)(addr), &_v, 4); } while (0)
#else
#include "drv.h"
#define CFG_RAM_GET8(addr)      PDATA_U8(addr)
#define CFG_RAM_SET8(addr,v)    do { PDATA_U8(addr) = (UINT8)(v); } while (0)
#define CFG_ROM_GET8(addr)      CODE_U8(addr)
#ifdef _CFG_DB_INTERNAL_
void   CFG_ROM_SET8 (IN UINT16 vAddr, IN UINT8  vData)  { EEPROM_MEMCPY(vAddr, &vData, sizeof(vData)); }
UINT16 CFG_RAM_GET16(IN UINT16 vAddr)                   { return PDATA_U16(vAddr); }
UINT16 CFG_ROM_GET16(IN UINT16 vAddr)                   { return CODE_U16(vAddr); }
void   CFG_RAM_SET16(IN UINT16 vAddr, IN UINT16 vData)  { PDATA_U16(vAddr) = vData; }
void   CFG_ROM_SET16(IN UINT16 vAddr, IN UINT16 vData)  { EEPROM_MEMCPY(vAddr, &vData, sizeof(vData)); }
UINT32 CFG_RAM_GET32(IN UINT16 vAddr)                   { return PDATA_U32(vAddr); }
UINT32 CFG_ROM_GET32(IN UINT16 vAddr)                   { return CODE_U32(vAddr); }
void   CFG_RAM_SET32(IN UINT16 vAddr, IN UINT32 vData)  { PDATA_U32(vAddr) = vData; }
void   CFG_ROM_SET32(IN UINT16 vAddr, IN UINT32 vData)  { EEPROM_MEMCPY(vAddr, &vData, sizeof(vData)); }
#else
void   CFG_ROM_SET8 (IN UINT16 vAddr, IN UINT8  vData);
UINT16 CFG_RAM_GET16(IN UINT16 vAddr);
UINT16 CFG_ROM_GET16(IN UINT16 vAddr);
void   CFG_RAM_SET16(IN UINT16 vAddr, IN UINT16 vData);
void   CFG_ROM_SET16(IN UINT16 vAddr, IN UINT16 vData);
UINT32 CFG_RAM_GET32(IN UINT16 vAddr);
UINT32 CFG_ROM_GET32(IN UINT16 vAddr);
void   CFG_RAM_SET32(IN UINT16 vAddr, IN UINT32 vData);
void   CFG_ROM_SET32(IN UINT16 vAddr, IN UINT32 vData);
#endif
#endif

#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_DB_ReadByte
 * DESCRIPTION:
 *   Read 8-bit data for I2C slave.
 * PARAMETERS:
 *   vOffset : offset to read.
 * RETURN:
 *   Read 8-bit data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
UINT8 CFG_DB_ReadByte(IN UINT8 vOffset);

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_DB_ReadByte
 * DESCRIPTION:
 *   Write flush data from I2C slave.
 * PARAMETERS:
 *   vOffset : offset to read.
 *   vCount  : flush buffer count.
 *   pBuf    : flush buffer.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_DB_WriteFlush
(
    IN       UINT8            vOffset,
    IN       UINT8            vCount,
    IN const UINT8 SEG_XDATA *pBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_DB_Init
 * DESCRIPTION:
 *   Configuration database init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.2.15        Panda.Xiong          Create
 *****************************************************************************/
#define CFG_DB_Init()       /* do nothing */

#endif

#endif


#endif /* __CFG_DB_H */

