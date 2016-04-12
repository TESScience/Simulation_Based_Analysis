#ifndef WARPSPEED_H
#define WARPSPEED_H

#include <stdint.h>

extern void warpspeed_seed( void *s, unsigned size );
extern uint32_t warpspeed_urand( void );

/*

The following constants define a shift register representing a primitive pentanomial mod
2. For CUDA, the tap values have to be >= the size of a thread block so we don't need
to compute serially. LENGTH must be twice the size of the thread block. For efficiency,
the thread block size should equal the hardware warp size.

*/

#define LENGTH 64
#define TAP1 32
#define TAP2 43
#define TAP3 57

#define RANDOM_FRAME_SIZE (LENGTH/2)

#endif /* ndef WARPSPEED_H */
