/* 
 * The Mersenne Twister pseudo-random number generator (PRNG)
 *
 * This is an implementation of fast PRNG called MT19937,
 * meaning it has a period of 2^19937-1, which is a Mersenne
 * prime.
 *
 * This PRNG is fast and suitable for non-cryptographic code.
 * For instance, it would be perfect for Monte Carlo simulations,
 * etc.
 *
 * This code has been designed as a drop-in replacement for libc rand and
 * srand().  If you need to mix them, you should encapsulate this code in a
 * namespace.
 *
 * Written by Christian Stigen Larsen
 * http://csl.name
 *
 * Distributed under the modified BSD license.
 *
 * 2015-02-17
 */

#ifndef MERSENNE_TWISTER_H
#define MERSENNE_TWISTER_H

#define __STDC_LIMIT_MACROS
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Maximum number you can get from rand().
 */
#define RAND_MAX INT32_MAX

/*
 * Initialize the number generator with given seed.
 * (LIBC REPLACEMENT FUNCTION)
 */
void srand(unsigned seed_value);

/*
 * Extract a pseudo-random integer in the range 0 ... RAND_MAX.
 * (LIBC REPLACEMENT FUNCTION)
 */
int rand();

/*
 * Extract a pseudo-random unsigned 32-bit integer in the range 0 ... UINT32_MAX
 */
uint32_t rand_u32();

/*
 * Combine two unsigned 32-bit pseudo-random numbers into one 64-bit
 */
uint64_t rand_u64();

/*
 * Initialize Mersenne Twister with given seed value.
 */
void seed(uint32_t seed_value);

/*
 * Return a random float in the CLOSED range [0, 1]
 * Mnemonic: randf_co = random float 0=closed 1=closed
 */
float randf_cc();

/*
 * Return a random float in the OPEN range [0, 1>
 * Mnemonic: randf_co = random float 0=closed 1=open
 */
float randf_co();

/*
 * Return a random float in the OPEN range <0, 1>
 * Mnemonic: randf_oo = random float 0=open 1=open
 */
float randf_oo();

/*
 * Return a random double in the CLOSED range [0, 1]
 * Mnemonic: randd_co = random double 0=closed 1=closed
 */
double randd_cc();

/*
 * Return a random double in the OPEN range [0, 1>
 * Mnemonic: randd_co = random double 0=closed 1=open
 */
double randd_co();

/*
 * Return a random double in the OPEN range <0, 1>
 * Mnemonic: randd_oo = random double 0=open 1=open
 */
double randd_oo();

#ifdef __cplusplus
} // extern "C"
#endif

static const unsigned SIZE   = 624;
static const unsigned PERIOD = 397;
static const unsigned DIFF   = SIZE-PERIOD;

static uint32_t MT[SIZE];
static unsigned index = 0;

#define M32(x) (0x80000000 & x) // 32nd Most Significant Bit
#define L31(x) (0x7FFFFFFF & x) // 31 Least Significant Bits
#define ODD(x) (x & 1) // Check if number is odd

#define UNROLL(expr) \
  y = M32(MT[i]) | L31(MT[i+1]); \
  MT[i] = MT[expr] ^ (y>>1) ^ MATRIX[ODD(y)]; \
  ++i;

static inline void generate_numbers()
{
  /*
   * Originally, we had one loop with i going from [0, SIZE) and
   * two modulus operations:
   *
   * for ( register unsigned i=0; i<SIZE; ++i ) {
   *   register uint32_t y = M32(MT[i]) | L31(MT[(i+1) % SIZE]);
   *   MT[i] = MT[(i + PERIOD) % SIZE] ^ (y>>1);
   *   if ( ODD(y) ) MT[i] ^= 0x9908b0df;
   * }
   *
   * For performance reasons, we've unrolled the loop three times, thus
   * mitigating the need for any modulus operations.
   *
   * Anyway, it seems this trick is old hat:
   * http://www.quadibloc.com/crypto/co4814.htm
   *
   */

  static const uint32_t MATRIX[2] = {0, 0x9908b0df};
  register uint32_t y, i=0;

  // i = [0 ... 225]
  while ( i<(DIFF-1) ) {
    /*
     * We're doing 226 = 113*2, an even number of steps, so we can
     * safely unroll one more step here for speed:
     */
    UNROLL(i+PERIOD);
    UNROLL(i+PERIOD);
  }

  // i = 226
  UNROLL((i+PERIOD) % SIZE);

  // i = [227 ... 622]
  while ( i<(SIZE-1) ) {
    /*
     * 623-227 = 396 = 2*2*3*3*11, so we can unroll this loop in any number
     * that evenly divides 396 (2, 4, 6, etc). Here we'll unroll 11 times.
     */
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
    UNROLL(i-DIFF);
  }

  // i = 623
  y = M32(MT[SIZE-1]) | L31(MT[0]); \
  MT[SIZE-1] = MT[PERIOD-1] ^ (y>>1) ^ MATRIX[ODD(y)]; \
}

extern "C" void seed(uint32_t value)
{
  /*
   * The equation below is a linear congruential generator (LCG),
   * one of the oldest known pseudo-random number generator
   * algorithms, in the form X_(n+1) = = (a*X_n + c) (mod m).
   *
   * We've implicitly got m=32 (mask + word size of 32 bits), so
   * there is no need to explicitly use modulus.
   *
   * What is interesting is the multiplier a.  The one we have
   * below is 0x6c07865 --- 1812433253 in decimal, and is called
   * the Borosh-Niederreiter multiplier for modulus 2^32.
   *
   * It is mentioned in passing in Knuth's THE ART OF COMPUTER
   * PROGRAMMING, Volume 2, page 106, Table 1, line 13.  LCGs are
   * treated in the same book, pp. 10-26
   *
   * You can read the original paper by Borosh and Niederreiter
   * as well.  It's called OPTIMAL MULTIPLIERS FOR PSEUDO-RANDOM
   * NUMBER GENERATION BY THE LINEAR CONGRUENTIAL METHOD (1983) at
   * http://www.springerlink.com/content/n7765ku70w8857l7/
   *
   * You can read about LCGs at:
   * http://en.wikipedia.org/wiki/Linear_congruential_generator
   *
   * From that page, it says:
   * "A common Mersenne twister implementation, interestingly
   * enough, uses an LCG to generate seed data.",
   *
   * Since we're using 32-bits data types for our MT array, we can skip the
   * masking with 0xFFFFFFFF below.
   */

  MT[0] = value;
  index = 0;

  for ( register unsigned i=1; i<SIZE; ++i )
    MT[i] = 0x6c078965*(MT[i-1] ^ MT[i-1]>>30) + i;
}

extern "C" uint32_t rand_u32()
{
  if ( !index )
    generate_numbers();

  register uint32_t y = MT[index];

  // Tempering
  y ^= y>>11;
  y ^= y<< 7 & 0x9d2c5680;
  y ^= y<<15 & 0xefc60000;
  y ^= y>>18;

  if ( ++index == SIZE )
    index = 0;

  return y;
}

extern "C" int rand()
{
  /*
   * PORTABILITY WARNING:
   *
   * rand_u32() uses all 32-bits for the pseudo-random number,
   * but rand() must return a number from 0 ... RAND_MAX.
   *
   * We'll just assume that rand() only uses 31 bits worth of
   * data, and that we're on a two's complement system.  
   *
   * So, to output an integer compatible with rand(), we have
   * two options: Either mask off the highest (32nd) bit, or
   * shift right by one bit.  Masking with 0x7FFFFFFF will be
   * compatible with 64-bit MT[], so we'll just use that here.
   *
   */
  return static_cast<int>(0x7FFFFFFF & rand_u32());
}

extern "C" void srand(unsigned value)
{
  seed(static_cast<uint32_t>(value));
}

extern "C" float randf_cc()
{
  return static_cast<float>(rand_u32())/UINT32_MAX;
}

extern "C" float randf_co()
{
  return static_cast<float>(rand_u32())/(UINT32_MAX+1.0f);
}

extern "C" float randf_oo()
{
  return (static_cast<float>(rand_u32())+0.5f)/(UINT32_MAX+1.0f);
}

extern "C" double randd_cc()
{
  return static_cast<double>(rand_u32())/UINT32_MAX;
}

extern "C" double randd_co()
{
  return static_cast<double>(rand_u32())/(UINT32_MAX+1.0);
}

extern "C" double randd_oo()
{
  return (static_cast<double>(rand_u32())+0.5)/(UINT32_MAX+1.0);
}

extern "C" uint64_t rand_u64()
{
  return static_cast<uint64_t>(rand_u32())<<32 | rand_u32();
}

#endif // MERSENNE_TWISTER_H