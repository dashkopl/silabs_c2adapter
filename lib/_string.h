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

