#ifndef CALRISSIAN_H
#define CALRISSIAN_H

#include <stdint.h>

void calrissian_srand_long( uint64_t seed );
extern void calrissian_srand( int seed );
extern uint32_t calrissian_urand( void );

#endif /* CALRISSIAN_H */
