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
 *   Extended string.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"


/******************************************************************************
 * FUNCTION NAME:
 *   _trimHead
 * DESCRIPTION:
 *   Trim the leading spaces of the input string.
 * PARAMETERS:
 *   pStr : Input string to trim, and output string after trimmed.
 * RETURN:
 *   The trimmed string.
 * NOTES:
 *   This API will modify the input string, please backup it first.
 * HISTORY:
 *   2012.7.19        Panda.Xiong         Create/Update
 *****************************************************************************/
char SEG_XDATA *_trimHead(IN OUT char SEG_XDATA *pStr)
{
    __nullCheck(pStr);

    if (!IsStrEmpty(pStr))
    {
        char SEG_XDATA *p;

        /* move to the end of leading spaces */
        p = pStr;
        while (IsSpace(*p))
        {
            p++;
        }

        /* copy the remain string, to remove the leading spaces */
        if (p != pStr)
        {
            strcpy(pStr, p);
        }
    }

    return pStr;
}


/******************************************************************************
 * FUNCTION NAME:
 *   _trimTail
 * DESCRIPTION:
 *   Trim the tailing spaces of the input string.
 * PARAMETERS:
 *   pStr : Input string to trim, and output string after trimmed.
 * RETURN:
 *   The trimmed string.
 * NOTES:
 *   This API will modify the input string, please backup it first.
 * HISTORY:
 *   2012.7.19        Panda.Xiong         Create/Update
 *****************************************************************************/
char SEG_XDATA *_trimTail(IN OUT char SEG_XDATA *pStr)
{
    __nullCheck(pStr);

    if (!IsStrEmpty(pStr))
    {
        char SEG_XDATA *p;

        /* point to the start of tailing spaces */
        p = pStr + strlen(pStr) - 1;
        while (IsSpace(*p))
        {
            p--;
        }

        /* mark the tailing spaces to invalid, to remove them */
        *(p+1) = '\0';
    }

    return pStr;
}


/******************************************************************************
 * FUNCTION NAME:
 *   _trim
 * DESCRIPTION:
 *   Trim the leading & tailing spaces of the input string.
 * PARAMETERS:
 *   pStr : Input string to trim, and output string after trimmed.
 * RETURN:
 *   The trimmed string.
 * NOTES:
 *   This API will modify the input string, please backup it first.
 * HISTORY:
 *   2012.7.19        Panda.Xiong         Create/Update
 *****************************************************************************/
char SEG_XDATA *_trim(IN OUT char SEG_XDATA *pStr)
{
    return _trimTail(_trimHead(pStr));
}


/******************************************************************************
 * FUNCTION NAME:
 *   _trimAll
 * DESCRIPTION:
 *   Trim the leading & tailing & inside spaces of the input string,
 *    the inside spaces will be trimmed to only one space.
 * PARAMETERS:
 *   pStr : Input string to trim, and output string after trimmed.
 * RETURN:
 *   The trimmed string.
 * NOTES:
 *   This API will modify the input string, please backup it first.
 * HISTORY:
 *   2012.7.19        Panda.Xiong         Create/Update
 *****************************************************************************/
char SEG_XDATA *_trimAll(IN OUT char SEG_XDATA *pStr)
{
    __nullCheck(pStr);

    if (!IsStrEmpty(pStr))
    {
        char SEG_XDATA *p;

        p = pStr;
        while (*p != '\0')
        {
            /* trim the leading spaces of this string section */
            p = _trimHead(p);

            /* skip the first non-space string section */
            while ((*p != '\0') && !IsSpace(*p))
            {
                p++;
            }

            if (*p == '\0')
            {
                break;
            }

            /* keep this space */
            *p++ = ' ';
        }
    }

    return _trimTail(pStr);
}

