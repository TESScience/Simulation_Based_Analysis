#include "squarissian.h"

/* Largest Sophie Germain prime less than 2^31 */

#define SGPRIME 32633

/* Associated safe prime */

#define SAFE (2*SGPRIME+1)

/* Linear congruential generator parameters */
/* From Numerical Recipes via Wikipedia */

#define LCMULT 1664525
#define LCADD 1013904223

/* State */

static uint32_t pseed, lcseed;

void squarissian_srand_long( uint64_t seed )
{
	pseed = seed%SAFE;
	if( pseed < 2) pseed = 2;
	lcseed = (uint32_t) seed;
}

void sqarissian_srand( int seed )
{
	squarissian_srand_long( (uint64_t) seed );
}

uint32_t squarissian_urand( void )
{
	uint32_t square = pseed * pseed;
	pseed = square % SAFE;
	lcseed = LCMULT * lcseed + LCADD;
	return square + lcseed;
}