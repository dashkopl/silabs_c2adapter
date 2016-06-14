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
 *   Extended stdio library.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef ___STDIO_H
#define ___STDIO_H


#if 0
  printf
  Summary #include <stdio.h>

  int printf (
    const char *fmtstr       /* format string */
    <[>, arguments ... <]>);   /* additional arguments */

  Description The printf function formats a series of strings and numeric values and builds a string to write to the output stream using the putchar function. The fmtstr argument is a format string that may be composed of characters, escape sequences, and format specifications.

  Ordinary characters and escape sequences are copied to the stream in the order in which they are interpreted. Format specifications always begin with a percent sign ('%') and require that additional arguments are included in the printf function call.

  The format string is read from left to right. The first format specification encountered references the first argument after fmtstr and converts and outputs it using the format specification. The second format specification accesses the second argument after fmtstr, and so on. If there are more arguments than format specifications, extra arguments are ignored. Results are unpredictable if there are not enough arguments for the format specifications or if the argument types do not match those specified by fmtstr.

  Format specifications have the following general format:

  % <[>flags<]> <[>width<]> <[>.precision<]> <[>{b|B|l|L}<]> type
  Each field in the format specification may be a single character or a number which specifies a particular format option.

  The type field is a single character that specifies whether the argument is interpreted as a character, string, number, or pointer, as shown in the following table.

  Type Argument Type Input Format
  d int Signed decimal number.
  u unsigned int Unsigned decimal number.
  o unsigned int Unsigned octal number.
  x unsigned int Unsigned hexadecimal number using "0123456789abcedf".
  X unsigned int Unsigned hexadecimal number using "0123456789ABCDEF".
  f float Floating-point number formatted as
  <[>-<]>dddd.dddd.
  e float Floating-point number formatted as
  <[>-<]>d.dddde<[>-<]>dd.
  E float Floating-point number formatted as
  <[>-<]>d.ddddE<[>-<]>dd.
  g float Floating-point number using either the e or f format, whichever is more compact for the specified value and precision.
  G float Floating-point number using either the E or f format, whichever is more compact for the specified value and precision.
  c char A single character.
  s * A string of characters terminated by a null character ('\0').
  p * A generic pointer formatted as t:aaaa where t is the memory type and aaaa is the hexadecimal address.

   Note

  The optional characters l or L may immediately precede the type character to respectively specify long types for d, i, u, o, x, and X.
  The optional characters b or B may immediately precede the type character to respectively specify char types for d, i, u, o, x, and X.
  Characters following a percent sign that are not recognized as a format specification are treated as ordinary characters. For example, "%%" writes a single percent sign to the output stream.

  The flags field is a single character used to justify the output and to print +/- signs and blanks, decimal points, and octal and hexadecimal prefixes, as shown in the following table.

  Flag Description
  - Left justify the output in the specified field width.
  + Prefix the output value with a + or - sign if the output is a signed type.
  blank (' ') Prefix the output value with a blank if it is a signed positive value. Otherwise, no blank is prefixed.
  # Prefixes a non-zero output value with 0, 0x, or 0X when used with o, x, and X field types, respectively.

  When used with the e, E, f, g, and G field types, the # flag forces the output value to include a decimal point.

  The # flag is ignored in all other cases.

  The width field is a non-negative number that specifies the minimum number of characters printed. If the number of characters in the output value is less than width, blanks are added on the left (by default) or right (when the - flag is specified) to pad to the minimum width. If width is prefixed with a '0', zeros are padded instead of blanks. The width field never truncates the output. If the length of the output value exceeds the specified width, all characters are output.

  The width field may be an asterisk ('*'), in which case an int argument from the argument list provides the width value. Specifying a 'b' in front of the asterisk specifies that the argument is an unsigned char.

  The precision field is a non-negative number that specifies the number of characters to print, the number of significant digits, or the number of decimal places. The precision field can cause truncation or rounding of the output value in the case of a floating-point number as specified in the following table.

  Type Precision Field Meaning
  d,u,o,x,X The precision field specifies the minimum number of digits that are included in the output value. Digits are not truncated if the number of digits in the argument exceeds that defined in the precision field. If the number of digits in the argument is less than the precision field, the output value is padded on the left with zeros.
  f The precision field specifies the number of digits to the right of the decimal point. The last digit is rounded.
  e,E The precision field specifies the number of digits to the right of the decimal point. The last digit is rounded.
  g,G The precision field specifies the maximum number of significant digits in the output value.
  s The precision field specifies the maximum number of characters in the output value. Excess characters are not output.
  c,p The precision field has no effect on these field types.

  The precision field may be an asterisk ('*'), in which case an int argument from the argument list provides the value. Specifying a 'b' in front of the asterisk specifies that the argument is an unsigned char.

   Note

  You must ensure that the argument type matches that of the format specification. You may use type casts to ensure that the proper type is passed to printf.
  This function is implementation-specific and is based on the operation of the _getkey and putchar functions. These functions, as provided in the standard library, read and write characters using the microcontroller's serial port. Custom functions may use other I/O devices.
  The total number of bytes that may be passed to this function is limited due to the memory restrictions imposed by the 8051. A maximum of 15 bytes may be passed in SMALL or COMPACT model. A maximum of 40 bytes may be passed in LARGE model.

  Return Value The printf function returns the number of characters actually written to the output stream.

  See Also gets, printf517, puts, scanf, scanf517, sprintf, sprintf517, sscanf, sscanf517, vprintf, vsprintf

  Example #include <stdio.h>

  void tst_printf (void) {
    char a = 1;
    int b  = 12365;
    long c = 0x7FFFFFFF;

    unsigned char x = 'A';
    unsigned int y  = 54321;
    unsigned long z = 0x4A6F6E00;

    float f = 10.0;
    float g = 22.95;

    char buf [] = "Test String";
    char *p = buf;

    printf ("char %bd int %d long %ld\n",a,b,c);
    printf ("Uchar %bu Uint %u Ulong %lu\n",x,y,z);
    printf ("xchar %bx xint %x xlong %lx\n",x,y,z);
    printf ("String %s is at address %p\n",buf,p);
    printf ("%f != %g\n", f, g);
    printf ("%*f != %*g\n", (int)8, f, (int)8, g);
  }


  Copyright ? Keil, An ARM Company. All rights reserved.

#endif


#if DRV_UART_SUPPORT
 #define NO_PENDING  (0)
 #define PENDING     (-1)

 int  _getchar(int pending);

 #define printf             printf      /* C51 library API */
 #define putchar(c)         putchar(c)  /* C51 library API */
 #define getchar(timeout)   _getchar(timeout)
#else
 static void __printf(void *fmt, ...) { if(fmt); }
 #define printf             __printf
 #define putchar(c)         /* do nothing */
 #define getchar(timeout)   /* do nothing */
#endif


#endif /* ___STDIO_H */

