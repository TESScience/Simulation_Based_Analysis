#include "squafib.h"

/* Largest Sophie Germain prime less than 2^31 */

#define SGPRIME 32633

/* Associated safe prime */

#define SAFE (2*SGPRIME+1)

/* Linear congruential generator parameters */
/* From Numerical Recipes via Wikipedia */

#define LCMULT 1664525
#define LCADD 1013904223

/* State */

static uint32_t pseed, fib1, fib2, lcseed;

void squafib_srand_long( uint64_t seed )
{
	pseed = seed%SAFE;
	if( pseed < 2) pseed = 2;
	fib1 = (uint32_t) seed;
	if( fib1 < 1 ) fib1 = 1;
	fib2 = (uint32_t) (seed<<32);
	lcseed = (uint32_t) seed;
}

void sqafib_srand( int seed )
{
	squafib_srand_long( (uint64_t) seed );
}

uint32_t squafib_urand( void )
{
	uint32_t fib = fib1 + fib2;
	uint32_t square = pseed * pseed;
	pseed = square % SAFE;
	fib1 = fib2;
	fib2 = fib;
	lcseed = LCMULT * lcseed + LCADD;
	return square + fib + lcseed;
}