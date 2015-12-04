
/* macros for fast random number generator */

#ifndef THREADRAND_H
#define THREADRAND_H

extern unsigned *_warpspeed_rnbp;
extern short _warpspeed_rncnt;
extern unsigned _warpspeed_nrnbuf();

extern void warpspeed_srand( int new );
extern int warpspeed_rand( void );
extern unsigned warpspeed_urand( void );

#endif /* ndef THREADRAND_H */
