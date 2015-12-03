/* 3/5/85 jpd */
/* macros for fast random number generator */

#ifndef RANDA_H
#define RANDA_H

extern unsigned *_rnbp;
extern short _rncnt;
extern unsigned _nrnbuf();

extern void randa_srand( int new );
extern int randa_rand( void );
extern unsigned randa_urand( void );

#endif /* ndef RANDA_H */
