/* 
 * CS:APP Data Lab 
 * 
 * Zhang Chao (Frodocz)
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

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* Use (x & y) to get bits that both 1; use ~(x | y) to get bits that both 0.
   * Do OR operation to get all bits of same value (x & y) | (~(x | y)), then Reverse to get the final XOR result.
   * Apply De Morgan's laws to use only ~ and & ops. Precedence ~ higher than & than ^ than |. 
   */
  // int p = ~x & y;
  // int q = x & ~y;
  // int r = ~(~p & ~q);
  // return r;
  return ~(x & y) & ~(~x & ~y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /* Shift 1 to the left 31 bits*/
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* Suppose x = tmax, then x + 1 = tmin, then take ~tmin we'll get tmax again. 
   * Do XOR of tmax and x. We will get 0 if x equals to tmax.
   * A special case is  -1 (111111...111) also satisfy it, we need to make sure x is not -1.
   */
  return !(~(x + 1) ^ x) & !!(~x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /* Construct y = 0xAAAAAAAA, x & y will produce y if all odd bits of x are 1.
   * if (x & y) ^ y == 0, then all odd bits are set to 1. 
   */
  // int y = 0xAA | (0xAA << 8) | (0xAA << 16) | (0xAA << 24); // y is 0xAAAAAAAA
  int a = 0xAA | (0xAA) << 8;
  int y = a << 16 | a; // y is 0xAAAAAAAA and saves 2 operations comparing to line 193
  return !((x & y) ^ y);
  // return !(~(x|(0x55+(0x55<<8)+(0x55<<16)+(0x55<<24)))); // Reverse way
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* A + ~A = -1; A + (-A) = 0 ==>  A = ~A + 1*/
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /* 0x30 = 00110000; 0x39 = 00111001
   * First check if the bits 4-7 represents 0x3
   * Then check if the bits 0-3 falls into 0~9
   * 1. if bit 3 is 0, satisfy
   * 2. if bit 3 is 1, and bits 1-2 is all 0
   */
  return (!((x >> 4) ^ 3)) & (!(x & 8) | (!(x & 6)));
  /* Straight forward way, same as (x - 0x30 >= 0) && (0x39 - x) >=0 */
  // int TMIN = 1 << 31;
  // return !((x + ~0x30 + 1) & TMIN) & !((0x39 + ~x + 1) & TMIN);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /* x != 0 return y else return z
   * key idea is find b = 0xFFFFFFFF and 0 when x is 0 or not 0
   * Let a = !!(x) and b = ~a + 1, then x = 0, b = 0; x != 0, b = 0xFFFFFFFF
   * Let yy = -y and zz = 0 when x = 0;
   * Let yy = 0 and zz = -z when x != 0;
   * The final result will be y + z + yy + zz; 
   */
  // int a = !!(x); // a = 0 if x = 0 else a = 1
  // int b = ~a + 1; // x = 0, b = 0; x != 0, b = 0xFFFFFFFF;
  // int yy = ~(y & ~b) + 1; // x = 0 ==> yy = -y; x != 0 ==> yy = 0;
  // int zz = ~(z & b) + 1; // x = 0 ==> zz = 0; x != 0 ==> zz = -z;
  // return y + yy + z + zz;

  // Less operator method using & with b: x = 0, y = 0, z = z; x != 0, y = y, z = 0
  // return (y & b) | (z & ~b);

  /* Better method, key idea is still find b = 0xFFFFFFFF and 0 when x is 0 or not 0, but one operation less
   * x = 0, t = 0xFFFFFFFF; x != 0, t = 0
   * x = 0, y = 0 ==> ~t & y; z = z = t & z;
   * x!= 0, y = y ==> ~t & y; z = 0 = t & z;
   */
  int b = ~(!x) + 1;
  return (~b & y) | (b & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* First we check if x and y are of same sign by comparing the MSB 
   * Then 2 different cases: (same sign consider overflow, otherwise y - x = y + (-x) won't overflow)
   * 1. x and y diffrent sign (c != 0), and x < 0 (c & a)
   * 2. x and y same sign (c = 0), and y - x > 0 (~x + 1 + y >> 31 is 0)
   */
  int a = x >> 31; // a < 0 --> 0x111111111...111; a >= 0 --> 0x0000000000...000
  int b = y >> 31; // b < 0 --> 0x111111111...111; b >= 0 --> 0x0000000000...000
  int c = a ^ b; // c = 0 if same sign, else (c = 0xFFFFFFFF = -1) if different sign
  int case1 = c & a; 
  int case2 = ~c & (!((~x + 1 + y) >> 31));
  return !!(case1 | case2);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /* If x == 0 return 0; else (x != 0) return 1. The target becomes to how to determine if x is not 0
   * Let -x = ~x + 1, then (x | -x) >> 31 will be 0 only when x = 0; otherwise it will result -1.
   */
  return ((x | (~x + 1)) >> 31) + 1;
}
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
  /* We need to count from left to right and find first 1's bit location, then + 1
   */
  int b16,b8,b4,b2,b1,b0;
  int flag = x >> 31;
  x = (flag & ~x) | (~flag & x);
  b16 = !!(x >> 16) << 4;
  x >>= b16;
  b8 = !!(x >> 8) << 3;
  x >>= b8;
  b4 = !!(x >> 4) << 2;
  x >>= b4;
  b2 = !!(x >> 2) << 1;
  x >>= b2;
  b1 = !!(x >> 1);
  x >>= b1;
  b0 = x;
  return b0 + b1 + b2 + b4 + b8 + b16 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // float result = sign * M * (2 ^ E);
  // sign bit = 31; k = 8, E bits = 30-23; fraction bits = 22-0
  int sign = uf & (1 << 31);
  unsigned exp = (uf >> 23) & 0xFF;
  if (exp == 0xFF) return uf; // NaN
  if (exp == 0x00) return (uf << 1) | sign; 
  exp = exp + 1;
  if (exp == 0xFF) {
    return 0x7F800000 | sign;
  } else {
    int frac = uf & 0x7FFFFF;
    return (frac | exp << 23) | sign;
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = uf & (1 << 31); // negative 0x80000000, positive 0x0.
  unsigned exp = (uf >> 23) & 0xFF;
  int frac = uf & 0x7FFFFF;
  int frac1 = frac | 0x800000;  // Add the hidden 1 in front of frac
  int biasedExp = exp - 127; // E = e - Bias, Bias = 127 = 0x7F, -bias = 0xFFFFFF81
  if (exp == 0xFF) return 0x80000000u; // if out of range, return 0x80000000
  if (exp == 0x00) return 0;  // if de-norm number, means its range is (-1, 1)

  if (biasedExp > 31) return 0x80000000u; // Overflow
  if (biasedExp < 0) return 0;

  if (biasedExp > 23) frac1 <<= (biasedExp - 23);
  else frac1 >>= (23 - biasedExp);

  if (sign) return ~frac1 + 1;  // if negative number
  else if (frac1 >> 31) return 0x80000000u;  // if frac1 overflows, return 0x80000000;
  else return frac1;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  int exp = x + 127;
  if (exp <= 0) return 0;
  if (exp >= 255) return 0xFF << 23;
  return exp << 23;
}
