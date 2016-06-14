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
 *   Configuration API related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_H
#define __CFG_H


#include "lib.h"

#if CFG_SUPPORT

#include "cfg_mempage.h"
#include "cfg_memmap.h"
#include "cfg_pwd.h"
#include "cfg_db.h"


/* configuration name alias */
#if 1
 #define CFG(name)              MEMMAP_OFFSET(name)
 #define CFG_HEAD(name)         CFG(name)
 #define CFG_TAIL(name)         ((CFG_HEAD(name) + MEMMAP_LEN(name)) - 1)
#endif


/* configuration operation API */
#if 1

/******************************************************************************
 * 8-bit operation:
 *****************************************************************************/
/* access 8-bit data, based on (name, offset) */
#define CFG_GETO8(name,o)       ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)?                        \
                                    /* RAM */     CFG_RAM_GET8(MEMMAP_LMA(name)+(UINT8)(o)) :           \
                                ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)?                        \
                                    /* ROM */     CFG_ROM_GET8(MEMMAP_LMA(name)+(UINT8)(o)) :           \
                                    /* unknown */ (UINT8)I2CS_INVALID_DATA))
#define CFG_SETO8(name,o,v)     do {                                                                    \
                                    if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)                   \
                                        /* RAM */                                                       \
                                        { CFG_RAM_SET8(MEMMAP_LMA(name)+(UINT8)(o), (UINT8)(v)); }      \
                                    else if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)              \
                                        /* ROM */                                                       \
                                        { CFG_ROM_SET8(MEMMAP_LMA(name)+(UINT8)(o), (UINT8)(v)); }      \
                                    else                                                                \
                                        /* unknown */                                                   \
                                        { /* do nothing */ }                                            \
                                } while (0)

/* access 8-bit data, based on (pid, offset) */
#define CFG_GETV8(pid,o)        (MEMPAGE_IsRAM(pid)?                                                    \
                                    /* RAM */     CFG_RAM_GET8(MEMPAGE_RAM_LMA(pid)+(UINT8)(o)) :       \
                                (MEMPAGE_IsROM(pid)?                                                    \
                                    /* ROM */     CFG_ROM_GET8(MEMPAGE_ROM_LMA(pid)+(UINT8)(o)) :       \
                                    /* unknown */ (UINT8)I2CS_INVALID_DATA))
#define CFG_SETV8(pid,o, v)     do {                                                                    \
                                    if (MEMPAGE_IsRAM(pid))                                             \
                                    {                                                                   \
                                        /* RAM */                                                       \
                                        CFG_RAM_SET8(MEMPAGE_RAM_LMA(pid)+(UINT8)(o), (UINT8)(v));      \
                                    }                                                                   \
                                    else if (MEMPAGE_IsROM(pid))                                        \
                                    {                                                                   \
                                        /* ROM */                                                       \
                                        CFG_ROM_SET8(MEMPAGE_ROM_LMA(pid)+(UINT8)(o), (UINT8)(v));      \
                                    }                                                                   \
                                    else                                                                \
                                    {                                                                   \
                                        /* unknown, do nothing */                                       \
                                    }                                                                   \
                                } while (0)

/* access 8-bit data, based on (name) */
#define CFG_GET8(name)          CFG_GETO8(name, 0)
#define CFG_SET8(name,v)        CFG_SETO8(name, 0, (v))

/******************************************************************************
 * 16-bit operation:
 *****************************************************************************/
/* access 16-bit data, based on (name, offset) */
#define CFG_GETO16(name,o)      ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)?                        \
                                    /* RAM */     CFG_RAM_GET16(MEMMAP_LMA(name)+(UINT8)(o)) :          \
                                ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)?                        \
                                    /* ROM */     CFG_ROM_GET16(MEMMAP_LMA(name)+(UINT8)(o)) :          \
                                    /* unknown */ (UINT16)I2CS_INVALID_DATA))
#define CFG_SETO16(name,o,v)    do {                                                                    \
                                    if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)                   \
                                        /* RAM */                                                       \
                                        { CFG_RAM_SET16(MEMMAP_LMA(name)+(UINT8)(o), (UINT16)(v)); }    \
                                    else if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)              \
                                        /* ROM */                                                       \
                                        { CFG_ROM_SET16(MEMMAP_LMA(name)+(UINT8)(o), (UINT16)(v)); }    \
                                    else                                                                \
                                        /* unknown */                                                   \
                                        { /* do nothing */ }                                            \
                                } while (0)

/* access 16-bit data, based on (pid, offset) */
#define CFG_GETV16(pid,o)        (MEMPAGE_IsRAM(pid)?                                                   \
                                    /* RAM */     CFG_RAM_GET16(MEMPAGE_RAM_LMA(pid)+(UINT8)(o)) :      \
                                (MEMPAGE_IsROM(pid)?                                                    \
                                    /* ROM */     CFG_ROM_GET16(MEMPAGE_ROM_LMA(pid)+(UINT8)(o)) :      \
                                    /* unknown */ (UINT16)I2CS_INVALID_DATA))
#define CFG_SETV16(pid,o, v)     do {                                                                   \
                                    if (MEMPAGE_IsRAM(pid))                                             \
                                    {                                                                   \
                                        /* RAM */                                                       \
                                        CFG_RAM_SET16(MEMPAGE_RAM_LMA(pid)+(UINT8)(o), (UINT16)(v));    \
                                    }                                                                   \
                                    else if (MEMPAGE_IsROM(pid))                                        \
                                    {                                                                   \
                                        /* ROM */                                                       \
                                        CFG_ROM_SET16(MEMPAGE_ROM_LMA(pid)+(UINT8)(o), (UINT16)(v));    \
                                    }                                                                   \
                                    else                                                                \
                                    {                                                                   \
                                        /* unknown, do nothing */                                       \
                                    }                                                                   \
                                } while (0)

/* access 16-bit data, based on (name) */
#define CFG_GET16(name)          CFG_GETO16(name, 0)
#define CFG_SET16(name,v)        CFG_SETO16(name, 0, (v))

/******************************************************************************
 * 32-bit operation:
 *****************************************************************************/
/* access 32-bit data, based on (name, offset) */
#define CFG_GETO32(name,o)      ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)?                        \
                                    /* RAM */     CFG_RAM_GET32(MEMMAP_LMA(name)+(UINT8)(o)) :          \
                                ((MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)?                        \
                                    /* ROM */     CFG_ROM_GET32(MEMMAP_LMA(name)+(UINT8)(o)) :          \
                                    /* unknown */ (UINT32)I2CS_INVALID_DATA))
#define CFG_SETO32(name,o,v)    do {                                                                    \
                                    if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_RAM)                   \
                                        /* RAM */                                                       \
                                        { CFG_RAM_SET32(MEMMAP_LMA(name)+(UINT8)(o), (UINT32)(v)); }    \
                                    else if (MEMMAP_LMA_TYPE(name) == MEMMAP_LMA_TYPE_ROM)              \
                                        /* ROM */                                                       \
                                        { CFG_ROM_SET32(MEMMAP_LMA(name)+(UINT8)(o), (UINT32)(v)); }    \
                                    else                                                                \
                                        /* unknown */                                                   \
                                        { /* do nothing */ }                                            \
                                } while (0)

/* access 32-bit data, based on (pid, offset) */
#define CFG_GETV32(pid,o)        (MEMPAGE_IsRAM(pid)?                                                   \
                                    /* RAM */     CFG_RAM_GET32(MEMPAGE_RAM_LMA(pid)+(UINT8)(o)) :      \
                                (MEMPAGE_IsROM(pid)?                                                    \
                                    /* ROM */     CFG_ROM_GET32(MEMPAGE_ROM_LMA(pid)+(UINT8)(o)) :      \
                                    /* unknown */ (UINT32)I2CS_INVALID_DATA))
#define CFG_SETV32(pid,o, v)     do {                                                                   \
                                    if (MEMPAGE_IsRAM(pid))                                             \
                                    {                                                                   \
                                        /* RAM */                                                       \
                                        CFG_RAM_SET32(MEMPAGE_RAM_LMA(pid)+(UINT8)(o), (UINT32)(v));    \
                                    }                                                                   \
                                    else if (MEMPAGE_IsROM(pid))                                        \
                                    {                                                                   \
                                        /* ROM */                                                       \
                                        CFG_ROM_SET32(MEMPAGE_ROM_LMA(pid)+(UINT8)(o), (UINT32)(v));    \
                                    }                                                                   \
                                    else                                                                \
                                    {                                                                   \
                                        /* unknown, do nothing */                                       \
                                    }                                                                   \
                                } while (0)

/* access 32-bit data, based on (name) */
#define CFG_GET32(name)          CFG_GETO32(name, 0)
#define CFG_SET32(name,v)        CFG_SETO32(name, 0, (v))

/******************************************************************************
 * bit-field operation:
 *****************************************************************************/
#define CFG_GET_BITO(name,o,ob)     ((CFG_GETO8(name,(o)) >> (MEMMAP_BIT(name)+((UINT8)(ob)*MEMMAP_LEN(name)))) & GET_MASK(0,MEMMAP_LEN(name)))
#define CFG_SET_BITO(name,o,ob,v)   do {                                                                                \
                                        UINT8   _v = (v);                                                               \
                                        if (CFG_GET_BITO(name,(o),(ob)) != (_v))                                        \
                                        {                                                                               \
                                            CFG_SETO8(name,                                                             \
                                                      (o),                                                              \
                                                      ( (CFG_GETO8(name,(o))                                            \
                                                           & ~(MEMMAP_BIT_MASK(name)<<((UINT8)(ob)*MEMMAP_LEN(name))))  \
                                                        | (((_v) & GET_MASK(0,MEMMAP_LEN(name)))                        \
                                                           << (MEMMAP_BIT(name)+((UINT8)(ob)*MEMMAP_LEN(name)))) ) );   \
                                        }                                                                               \
                                    } while (0)
#define CFG_GET_BIT(name)           CFG_GET_BITO(name, 0, 0)
#define CFG_SET_BIT(name,v)         CFG_SET_BITO(name, 0, 0, (v))

/******************************************************************************
 * DDM operation:
 *****************************************************************************/
#define CFG_SET_DDM(name,v)     CFG_SET16(name, (v))

/******************************************************************************
 * unified API:
 *****************************************************************************/
#define CFG_GET(name)           ((MEMMAP_TYPE(name) == MEMMAP_TYPE_UNIT)?                           \
                                  /* memory unit */                                                 \
                                    ((MEMMAP_LEN(name)==2)? CFG_GET16(name) : /* 16-bit  */         \
                                    ((MEMMAP_LEN(name)==4)? CFG_GET32(name) : /* 32-bit  */         \
                                    CFG_GET8(name))) :                        /* 8-bit / unknown */ \
                                  /* memory bit */                                                  \
                                    CFG_GET_BIT(name))
#define CFG_SET(name,v)         do {                                                                \
                                    if (MEMMAP_TYPE(name) == MEMMAP_TYPE_UNIT)                      \
                                    {                                                               \
                                        /* memory unit */                                           \
                                        if (MEMMAP_LEN(name) == 2)                                  \
                                            /* 16-bit */                                            \
                                            { CFG_SET16(name, (v)); }                               \
                                        else if (MEMMAP_LEN(name) == 4)                             \
                                            /* 32-bit */                                            \
                                            { CFG_SET32(name, (v)); }                               \
                                        else                                                        \
                                            /* 8-bit / others */                                    \
                                            { CFG_SET8(name, (v)); }                                \
                                    }                                                               \
                                    else                                                            \
                                    {                                                               \
                                        /* memory bit */                                            \
                                        CFG_SET_BIT(name, (v));                                     \
                                    }                                                               \
                                } while (0)

#endif


#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_Entry
 * DESCRIPTION:
 *   Configuration Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define CFG_Entry()         /* do nothing */

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_Init
 * DESCRIPTION:
 *   Configuration Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_Init(void);

#endif

#else
 #define CFG_Entry()        /* do nothing */
 #define CFG_Init()         /* do nothing */
#endif


#endif /* __CFG_H */

