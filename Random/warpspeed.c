
#include "warpspeed.h"
#include <string.h>

/*

For the serial implementation we need to store the currently active block of pseudo-random 
numbers in an array, but it would just be a register per thread in CUDA.

*/

static uint32_t history[ LENGTH ];
static uint32_t current[ RANDOM_FRAME_SIZE ];
static int idx;

/*

The if() clause and for() loop here are artifacts of the serial implementation. For the
parallel implementation we refesh in parallel every call. The memcpy() calls become
simple assigments. Note that here, the refresh is backwards with respect to the shift
register order, but by design the order doesnt matter.

*/

uint32_t warpspeed_urand( void )
{
	int i;
	
	if( idx < 0 ) {	// refresh the current block
		
		(void) memcpy( history + RANDOM_FRAME_SIZE, history, RANDOM_FRAME_SIZE * sizeof(uint32_t));
		(void) memcpy( history, current, RANDOM_FRAME_SIZE * sizeof(uint32_t));
		
		for( i = 0; i < RANDOM_FRAME_SIZE; i += 1 ) {
			current[i] = history[ i + TAP1 - RANDOM_FRAME_SIZE ]
				+ history[ i + TAP2 - RANDOM_FRAME_SIZE ]
				+ history[ i + TAP3 - RANDOM_FRAME_SIZE ]
				+ history[ i + LENGTH - RANDOM_FRAME_SIZE ];
		}
		idx = RANDOM_FRAME_SIZE - 1;
	}
	
	return current[ idx-- ];
}

/*

For initialization, use progressive values of a simple polynomial hash
of a seed string.

Starting with a messy constant prime insures at least one odd number in the state (a
requirement), and propagates plenty of bits into the history. After we've seeded
the history, we "shake well", generating enough numbers to
thoroughly scramble even a very regular initial state.

*/

void warpspeed_seed( void *s, unsigned size )
{
	uint8_t *sp = s;
	uint32_t hash = 0xeebd22e1;
	unsigned i;
	
	for( i = 0; i < LENGTH; i += 1 ) {
		history[ i ] = hash;
		hash = 0x16f * hash + sp[ i % size ];
	}
	
	idx = -1;
	
	for( i = 0; i < 20 * LENGTH; i += 1) (void) warpspeed_urand();	
}
