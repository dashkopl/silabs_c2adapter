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

