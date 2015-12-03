#ifndef SQUARISSIAN_H
#define SQUARISSIAN_H

#include <stdint.h>

void squarissian_srand_long( uint64_t seed );
extern void squarissian_srand( int seed );
extern uint32_t squarissian_urand( void );

#endif /* SQUARISSIAN_H */
