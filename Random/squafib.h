#ifndef SQUAFIB_H
#define SQUAFIB_H

#include <stdint.h>

void squafib_srand_long( uint64_t seed );
extern void squafib_srand( int seed );
extern uint32_t squafib_urand( void );

#endif /* SQUAFIB_H */
