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
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __BASE_MACRO_H
#define __BASE_MACRO_H


/* volatile/none-volatile address access */
#define VP32                *(volatile UINT32 *)
#define VP16                *(volatile UINT16 *)
#define VP8                 *(volatile UINT8  *)
#define P32                 *(UINT32 *)
#define P16                 *(UINT16 *)
#define P8                  *(UINT8  *)

/* combined macro generation, maximum 5 level delay expanding */
#define _COMBINE2_DELAY0(a,b)       a##b
#define _COMBINE3_DELAY0(a,b,c)     a##b##c
#define _COMBINE4_DELAY0(a,b,c,d)   a##b##c##d
#define _COMBINE2_DELAY1(a,b)       _COMBINE2_DELAY0(a,b)
#define _COMBINE2_DELAY2(a,b)       _COMBINE2_DELAY1(a,b)
#define _COMBINE2_DELAY3(a,b)       _COMBINE2_DELAY2(a,b)
#define _COMBINE2_DELAY4(a,b)       _COMBINE2_DELAY3(a,b)
#define _COMBINE2_DELAY5(a,b)       _COMBINE2_DELAY4(a,b)
#define _COMBINE3_DELAY1(a,b,c)     _COMBINE3_DELAY0(a,b,c)
#define _COMBINE3_DELAY2(a,b,c)     _COMBINE3_DELAY1(a,b,c)
#define _COMBINE3_DELAY3(a,b,c)     _COMBINE3_DELAY2(a,b,c)
#define _COMBINE3_DELAY4(a,b,c)     _COMBINE3_DELAY3(a,b,c)
#define _COMBINE3_DELAY5(a,b,c)     _COMBINE3_DELAY4(a,b,c)
#define _COMBINE4_DELAY1(a,b,c,d)   _COMBINE4_DELAY0(a,b,c,d)
#define _COMBINE4_DELAY2(a,b,c,d)   _COMBINE4_DELAY1(a,b,c,d)
#define _COMBINE4_DELAY3(a,b,c,d)   _COMBINE4_DELAY2(a,b,c,d)
#define _COMBINE4_DELAY4(a,b,c,d)   _COMBINE4_DELAY3(a,b,c,d)
#define _COMBINE4_DELAY5(a,b,c,d)   _COMBINE4_DELAY4(a,b,c,d)
#define COMBINE(a,b)                _COMBINE2_DELAY5(a,b)
#define COMBINE2(a,b)               _COMBINE2_DELAY5(a,b)
#define COMBINE3(a,b,c)             _COMBINE3_DELAY5(a,b,c)
#define COMBINE4(a,b,c,d)           _COMBINE4_DELAY5(a,b,c,d)

/* Calculate the total element of an array.
 *
 * e.g:
 *   int  array[100];
 *  To get the total element of (array), just use COUNT_OF(array).
 *   acturally, the total element in this sample is 100.
 */
#define COUNT_OF(n)         (SINT32)(sizeof(n) / sizeof((n)[0]))

/* calculate the Byte Offset of member in struct.
 *
 * e.g:
 *  typedef struct
 *  {
 *      int  a;
 *      int  b;
 *      char c;
 *  } TYPE_S;
 *
 * To get the Byte Offset of (c) in TYPE_S, just use offsetof(TYPE_S, c).
 *  acturally, the offset in this sample is 8.
 */
#undef offsetof
#ifdef __compiler_offsetof
 #define offsetof(type, member)  __compiler_offsetof(type, member)
#else
 #define offsetof(type, member)  ((size_t) &((type *)0)->member)
#endif

/* bit operation */
#define SET_BIT(n, b)       do { (n) |= (1U << (UINT8)(b));  } while (0)
#define CLR_BIT(n, b)       do { (n) &= ~(1U << (UINT8)(b)); } while (0)
#define READ_BIT(n, b)      ((BOOL)(((n) >> (UINT8)(b)) & 1U))
#define REVERSE_BIT(n, b)   do { (n) ^= (1U << (UINT8)(b)); } while (0)
#define WRITE_BIT(n, b, v)  do { (n) = ((n) & ~(1U << (UINT8)(b))) | ((UINT32)(v) << (UINT8)(b)); } while (0)

/* remove warning */
#define NO_WARNING(x)       do { if (x) {} } while (0)

/* Limit value API */
#define LIMIT_U16(x)    (((x) >=  65535L)? (UINT16)(0xFFFF) :               \
                         ((x) <=       0)? (UINT16)(0x0000) :               \
                                           (UINT16)(x))
#define LIMIT_S16(x)    (((x) >=  32767L)? (SINT16)(0x7FFF) :               \
                         ((x) <= -32768L)? (SINT16)(0x8000) :               \
                                           (SINT16)(x))

#define LIMIT_U8(x)     (((x) >=  255L)? (UINT8)(0xFF) :                    \
                         ((x) <=     0)? (UINT8)(0x0000) :                  \
                                         (UINT8)(x))
#define LIMIT_S8(x)     (((x) >=  127L)? (SINT8)(0x7F) :                    \
                         ((x) <= -128L)? (SINT8)(0x80) :                    \
                                         (SINT8)(x))

/* Get mask.
 *
 * e.g:
 *   if get 10-bit mask started from bit0, it will return 0x3FF.
 *   if get 10-bit mask started from bit5, it will return 0x7FE0.
 *
 * Note:
 *   1. the range of (start) : 0 <= start <= 31
 *      the range of (n)     : 0 <= n <= 31
 *   2. by default, this will return 32-bit mask, if only need 8-bit or 16-bit mask,
 *      you should limit the result like this:
 *         8-bit :  (UINT8)(GET_MASK(0, 5))  --- Start from bit0, occupy 5 bits;
 *        16-bit : (UINT16)(GET_MASK(3, 7))  --- Start from bit3, occupy 7 bits;
 */
#define GET_MASK(start, n)  ((~(0xFFFFFFFFUL << (UINT8)(n))) << (UINT8)(start))

/* get the absolute value */
#define ABS_8(x)    (((SINT8) (x) >= 0) ? (UINT8) (x) : (((SINT8) (x) == (SINT8) 0x80)       ? 0x7FU        : (UINT8) (0-(SINT8) (x))))
#define ABS_16(x)   (((SINT16)(x) >= 0) ? (UINT16)(x) : (((SINT16)(x) == (SINT16)0x8000)     ? 0x7FFFU      : (UINT16)(0-(SINT16)(x))))
#define ABS_32(x)   (((SINT32)(x) >= 0) ? (UINT32)(x) : (((SINT32)(x) == (SINT32)0x80000000L)? 0x7FFFFFFFUL : (UINT32)(0-(SINT32)(x))))

/* operate memory as big-endian */
#define SET_BE_16(buf, val)                                                 \
    do {                                                                    \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >> 8) & 0xFFUL);       \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >> 0) & 0xFFUL);       \
    } while (0)
#define GET_BE_16(buf) (UINT16)(  ((UINT16)((const UINT8 *)(buf))[0] << 8)  \
                                | ((UINT16)((const UINT8 *)(buf))[1] << 0))
#define SET_BE_32(buf, val)                                                 \
    do {                                                                    \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >> 24) & 0xFFUL);      \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >> 16) & 0xFFUL);      \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >>  8) & 0xFFUL);      \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >>  0) & 0xFFUL);      \
    } while (0)
#define GET_BE_32(buf) (  ((UINT32)((const UINT8 *)(buf))[0] << 24)         \
                        | ((UINT32)((const UINT8 *)(buf))[1] << 16)         \
                        | ((UINT32)((const UINT8 *)(buf))[2] <<  8)         \
                        | ((UINT32)((const UINT8 *)(buf))[3] <<  0))

/* operate memory as little-endian */
#define SET_LE_16(buf, val)                                                 \
    do {                                                                    \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT16)(val) >> 0) & 0xFFUL);       \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT16)(val) >> 8) & 0xFFUL);       \
    } while (0)
#define GET_LE_16(buf) (UINT16)(  ((UINT16)((const UINT8 *)(buf))[0] << 0)  \
                                | ((UINT16)((const UINT8 *)(buf))[1] << 8))
#define SET_LE_32(buf, val)                                                 \
    do {                                                                    \
        ((UINT8 *)(buf))[0] = (UINT8)(((UINT32)(val) >>  0) & 0xFFUL);      \
        ((UINT8 *)(buf))[1] = (UINT8)(((UINT32)(val) >>  8) & 0xFFUL);      \
        ((UINT8 *)(buf))[2] = (UINT8)(((UINT32)(val) >> 16) & 0xFFUL);      \
        ((UINT8 *)(buf))[3] = (UINT8)(((UINT32)(val) >> 24) & 0xFFUL);      \
    } while (0)
#define GET_LE_32(buf) (  ((UINT32)((const UINT8 *)(buf))[0] <<  0)         \
                        | ((UINT32)((const UINT8 *)(buf))[1] <<  8)         \
                        | ((UINT32)((const UINT8 *)(buf))[2] << 16)         \
                        | ((UINT32)((const UINT8 *)(buf))[3] << 24))


#endif /* __BASE_MACRO_H */

