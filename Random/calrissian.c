#include "calrissian.h"

/* Largest Sophie Germain prime less than 2^31 */

#define SGPRIME (((uint64_t)1<<31)-105)

/* Associated safe prime */

#define SAFE (2*SGPRIME+1)

/* Linear congruential generator parameters */
/* From Numerical Recipes via Wikipedia */

#define LCMULT 1664525
#define LCADD 1013904223

/* State */

static uint32_t pseed, lcseed;

void calrissian_srand_long( uint64_t seed )
{
	pseed = seed%SAFE;
	if( pseed < 2) pseed = 2;
	lcseed = (uint32_t) seed;
}

void calrissian_srand( int seed )
{
	calrissian_srand_long( (uint64_t) seed );
}

uint32_t calrissian_urand( void )
{
	pseed = ( (uint64_t) pseed * (uint64_t) pseed ) % SAFE;
	lcseed = LCMULT * lcseed + LCADD;
	return pseed + lcseed;
}