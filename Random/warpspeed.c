
#include "warpspeed.h"


/* The following constants define
   a primitive trinomial mod 2.
*/

#define LENGTH 32	// Match a CUDA warp
#define TAP1 2
#define TAP2 7
#define TAP3 16

unsigned *_warpspeed_rnbp;
short _warpspeed_rncnt = 0;
unsigned _warpspeed_nrnbuf();

static char inited = 0;
static unsigned rnbuf[ LENGTH ];

void warpspeed_srand( int new )
{
	unsigned *p = rnbuf + LENGTH;
	unsigned rnew = new;
	unsigned c;

	*--p = 1;

	while( p > rnbuf ) {
		*--p =  rnew;
		rnew >>= 1;
	}
	inited = 1;		/* Avoid recursive call from _nrnbuf! */

	for( c = -1; c != 0; c >>= 1 ) _warpspeed_nrnbuf();	/* Shake Well */

	_warpspeed_rncnt = 0;		/* start at consistent phase */
}


/* Fill the buffer with fresh random numbers */

unsigned _warpspeed_nrnbuf( void )
{
	unsigned j;

	if( ! inited ) warpspeed_srand( 1 );

	for(j = 0; j < LENGTH; j += 1) {
		rnbuf[j] += rnbuf[(j+TAP1)%LENGTH] 
			+ rnbuf[(j+TAP2)%LENGTH]
			+ rnbuf[(j+TAP3)%LENGTH];
	}
	_warpspeed_rnbp = rnbuf + LENGTH - 2;
	_warpspeed_rncnt = LENGTH - 1;
	return( rnbuf[ LENGTH - 1 ]);
}


int warpspeed_rand( void )		/* For things that don't use the macro */
{
	if( --_warpspeed_rncnt < 0 ) return( _warpspeed_nrnbuf() >> 1 );
	else return( *_warpspeed_rnbp-- >> 1 );
}

unsigned warpspeed_urand( void )	/* For things that don't use the macro */
{
	if( --_warpspeed_rncnt < 0 ) return( _warpspeed_nrnbuf());
	else return( *_warpspeed_rnbp-- );
}
