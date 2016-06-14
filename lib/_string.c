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

