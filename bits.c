/* 
 * CS:APP Data Lab 
 * 
 * 刘可欣 2248226242
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
// Rating 1
/* 
 * tmin - return minimum two's complement integer  最小补码（最负）-2^31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * upperBits - pads n upper bits with 1's //看例子来说不涉及拓展，只是生成一个高n位为1其余补0的数？
 *  You may assume 0 <= n <= 32
 *  Example: upperBits(4) = 0xF0000000 一个数高4位是1，其余为0
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 1
 */
int upperBits(int n) {
  //return (-1 << (32-n)) * (!!n);  //我错了符号违规。用-1（32个1）为基底，左移使除了前n位都补0；n=0时return 0
  return (~0 << (32 + (~n+1))) & ((!!n) << 31 >> 31);  //利用x&1=x,x&0=0，所以要全1或全0
}
// Rating 2
/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative 正负0判断
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
   return (!!x) | !!(x>>31) | (x>>31);
}
/* 

 * copyBit(x,n) - set all bits of result to bit n of x

 *   Bits numbered from 0 (LSB) to 31 (MSB)

 *   Examples: copyBit(6,0) = 0xFFFFFFFF, copyBit(5,1) = 0x00000000

 *   Legal ops: ! ~ & ^ | << >>

 *   Max ops: 8

 *   Rating: 2

 */
int copyBit(int x, int n) {
  return ((x >> n) & 1) << 31 >> 31 ;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1 考虑符号位！以及不要溢出了
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //错误，用排除法做了，n是32会溢出，再看后面也有很大问题以及违规了
  //return !((x & ~0x80000000) >> n) & ((!(x ^ 0x80000000) | !(x ^ 0x7FFFFFFF)) & !(n ^ 32));

  //int mask = 0x7F;
  //mask = (mask << 24) | (0xFF << 16) | (0xFF << 8) | 0xFF;
  //return !((x & mask) >> (n + ~0));
   int shift = 32 + (~n + 1);
   int y = (x << shift) >> shift;
   return !(x ^ y);
}
/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) {
   int mask = (0xAA << 24) | (0xAA << 16) | (0xAA << 8) | 0xAA;
   return !!(x & mask); //清零偶数位若不为0则说明奇数位上有1
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
  return !!(x ^ (~x+1));
}
// Rating 3
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
   //int minus = x + (~y+1); //会溢出，要解决很麻烦感觉在lab很难实现（判断溢出？
   //return !(minus >> 31) & (x ^ y);
   
   //先判断符号，分两种情况再|，符号相同相减不会溢出
   int x_sym = (x >> 31) & 1; //取符号位记得考虑算术右移补位，用&1
   int y_sym = (y >> 31) & 1;
   int same_diff = x_sym ^ y_sym;
   int minus_sym = ((x + (~y+1)) >> 31) & 1;
   //return (same_diff & (x_sym ^ 1)) | (!same_diff & !minus_sym); //都为最小负数会出错
   int result = (same_diff & (x_sym ^ 1)) | (!same_diff & !minus_sym);
   int if_same = !!(x ^ y) << 31 >> 31; //相同为0，清零result；不同全1，result不变 //记得^是位操作
   return result & if_same;
}
/* 
 * isAbsEqual - return 1 if |x| == |y|, and 0 otherwise 
 *   Examples: isAbsEqual(-5,5) = 1, isAbsEqual(4,5) = 0
 *   Legal ops: ! ^ + //注意限制
 *   Max ops: 12
 *   Rating: 3
 */
int isAbsEqual(int x, int y) {
   //x和y异或为0，或者不为零但相加为0
   //即返回1时两个判断必有一个为1一个为0，除了最小数相加溢出会等于0，所以这种唯一情况两个判断都为1也是返回1
   int same_diff = !(x ^ y);
   int plus_sym = !(x + y);
   //return same_diff | plus_sym; //一不小心就开始用&|了，但这个方法是成功的
   //改写下在0/1下可以实现和|同样效果的代码，即两者都为0才输出0
   return !(!(same_diff + plus_sym));
}
// Rating 4
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
   //找最高有效位，正数找1，负数可以取反找1

   //int x_sym = (x >> 31) & 1;
   //x = (!x_sym << 31) & x; //写错了，不过可以用来清零符号位
   int bits = 0, bits_1, bits_2, bits_3, bits_4; //要在函数开头声明？

   int shift = x >> 31; //全0或全1
   x = (shift & ~x) | (~shift & x);
   //int bits_15 = 15, sign = bits >> 15 << 15;
   //bits = (sign >> 15) & bits;
   //枚举不行，要二分排查，步长16 8 4 2 1
   bits = !!(x >> 16) << 4 ; //高16位有1则记16，没有则0
   x = x >> (!!(bits ^ 0) << 4); //bits有变化则清掉低16位，没有则不动

   bits_1 = ((!!(x >> 8)) << 3) + bits; //更新位数
   x = x >> (!!(bits_1 ^ bits) << 3);

   bits_2 = ((!!(x >> 4)) << 2) + bits_1;
   x = x >> (!!(bits_2 ^ bits_1) << 2);

   bits_3 = ((!!(x >> 2)) << 1) + bits_2;
   x = x >> (!!(bits_3 ^ bits_2) << 1);

   bits_4 = (!!(x >> 1)) + bits_3;
   x = x >> !!(bits_4 ^ bits_3);

   return bits_4 + x + 1; //加上符号位
}
