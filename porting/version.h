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
 *   Firmware version related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __VERSION_H
#define __VERSION_H


#ifdef __assemble__

/******************************************************************************
 * firmware version definition, read-only.
 *  format: aaa-bbbb-cc-dd-ee-ff
 *           -> aaa-bbbb-cc : firmware ID
 *               -> aaa  : firmware type
 *               -> bbbb : product id
 *               -> cc   : product branch id
 *           -> dd-ee-ff    : firmware revision
 *               -> dd   : configuration revision
 *               -> ee   : function revision
 *               -> ff   : bug-fixing revision
 *****************************************************************************/
#define FW_VERSION                                                          \
        0x05, 0x10,     /* firmware type          */                        \
        0xFF, 0xFF,     /* product id             */                        \
        0x00,           /* product branch id      */                        \
        0x00,           /* configuration revision */                        \
        0x01,           /* function revision      */                        \
        0x02            /* bug-fixing revision    */

#else

typedef struct
{
    UINT32  vMcuType;           /* mcu type                 */
    UINT32  vImageType;         /* image type               */
    UINT8   aFileVersion[8];    /* file version             */
    UINT32  vFileUDF;           /* file user-defined-field  */
    UINT32  vFileContentSize;   /* file content size        */
    UINT32  vFilePaddedSize;    /* file padded size         */
    UINT32  vFileChecksum;      /* file checksum            */
} FW_SIG_T;
extern FW_SIG_T SEG_CODE    __sig;
#define FW_VERSION(n)       (__sig.aFileVersion[(n)])

#endif


#endif /* __VERSION_H */

