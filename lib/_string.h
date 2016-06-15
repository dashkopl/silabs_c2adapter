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

#ifndef ___STRING_H
#define ___STRING_H


#define IsNullPointer(a)        ((a) == NULL)
#define __nullCheck(x)          /* empty */

#define IsSpace(x)              (((x)==' ') || ((x)=='\t'))
#define IsDigit(x)              (((x)>='0') && ((x)<='9'))
#define IsAlphabet(x)           ((((x)>='a') && ((x)<='z')) || (((x)>='A') && ((x)<='Z')))
#define IsXDigit(x)             (IsDigit(x)                             \
                                    || (((x)>='a') && ((x)<='f'))       \
                                    || (((x)>='A') && ((x)<='F')))
#define ToUpper(x)              ((((x)>='a') && ((x)<='z')) ? ((char)(((x)-'a')+'A')) : (x))
#define ToLower(x)              ((((x)>='A') && ((x)<='Z')) ? ((char)(((x)-'A')+'a')) : (x))


/* check string is equal */
#define IsStrEqual(a, b)        ((!IsNullPointer(a) && !IsNullPointer(b)) ? (strcmp((a), (b)) == 0) : FALSE)
#define IsStrEqual2(a, b)       ((!IsNullPointer(a) && !IsNullPointer(b)) ? (stricmp((a), (b)) == 0) : FALSE)
#define IsStrEqual3(a, b, n)    ((!IsNullPointer(a) && !IsNullPointer(b)) ? (strncmp((a), (b), (n)) == 0) : FALSE)
#define IsStrEqual4(a, b, n)    ((!IsNullPointer(a) && !IsNullPointer(b)) ? (strnicmp((a), (b), (n)) == 0) : FALSE)

/* check can find string/char b in string a? */
#define ContainStr(a, b)        ((!IsNullPointer(a) && !IsNullPointer(b))? !IsNullPointer(strstr((a), (b))) : FALSE)
#define ContainChar(a, b)       (!IsNullPointer(a)? !IsNullPointer(strchr((a), (b))) : FALSE)

/* check string is empty */
#define IsStrEmpty(a)           (strlen(a) == 0)

/* return the string end address, i.e. the '\0' character address */
#define StrEnd(s)               ((s) + strlen(s))


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
char SEG_XDATA *_trimHead(IN OUT char SEG_XDATA *pStr);

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
char SEG_XDATA *_trimTail(IN OUT char SEG_XDATA *pStr);

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
char SEG_XDATA *_trim(IN OUT char SEG_XDATA *pStr);

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
char SEG_XDATA *_trimAll(IN OUT char SEG_XDATA *pStr);


#endif /* ___STRING_H */

