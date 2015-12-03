/* Put random numbers to standard output */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "randa_macros.h"
#include "calrissian.h"
#include "squarissian.h"
#include "squafib.h"

void usage( void )
{
	fprintf( stderr, "usage: random [ -n bytecount ] [ -s seed ] [--<generator>]\n" );
	fprintf( stderr, "generators:\n" );
	fprintf( stderr, "additive (default)\n" );
	fprintf( stderr, "calrissian\n" );
	fprintf( stderr, "squarissian\n" );
	fprintf( stderr, "squafib\n" );
	exit( -1 );
}


int main( int argc, char *argv[] )
{
	unsigned rnum;
	uint64_t seed;
	int numbytes;
	int forever = 1;
	int i;
	struct timeval tv;
	enum { additive, calrissian, squarissian, squafib } gen = additive;

	(void) gettimeofday( &tv, NULL );
	
	seed = 1000000 * (uint64_t) tv.tv_sec + tv.tv_usec;	/* random start */

	while( *++argv ) {	/* process args */

		if( strcmp( *argv, "-n" ) == 0 ) { /* get byte count */
			forever = 0;
			if( ! *++argv ) usage();
			if( sscanf( *argv, "%d", &numbytes ) != 1 ) usage();
			continue;
		}

		if( strcmp( *argv, "-s" ) == 0 ) { /* get random seed */
			if( ! *++argv ) usage();
			seed = 0;
			i = 0;
			while( (*argv)[i] )
				seed = 10 * seed + ( (*argv)[i++] - '0' );
			continue;
		}
		
		if( strcmp( *argv, "--calrissian" ) == 0 ) {
			gen = calrissian;
			continue;
		}

		if( strcmp( *argv, "--squarissian" ) == 0 ) {
			gen = squarissian;
			continue;
		}

		if( strcmp( *argv, "--additive" ) == 0 ) {
			gen = additive;
			continue;
		}

		if( strcmp( *argv, "--squafib" ) == 0 ) {
			gen = squafib;
			continue;
		}

		usage();
	}

	switch( gen ) {
		case additive:
		randa_srand( (int) seed );
		break;
		
		case calrissian:
		calrissian_srand_long( seed );
		break;
		
		case squarissian:
		squarissian_srand_long( seed );
		break;
		
		case squafib:
		squafib_srand_long( seed );
		break;
	}

	for(;;) {
		
		switch( gen ) {
			
			case additive:
			rnum = randa_urand();
			break;
			
			case calrissian:
			rnum = calrissian_urand();
			break;
			
			case squarissian:
			rnum = squarissian_urand();
			break;
			
			case squafib:
			rnum = squafib_urand();
			break;
		}
		
		if( forever || numbytes >= sizeof( unsigned )) {
			fwrite( &rnum, sizeof( unsigned ), 1, stdout );
			numbytes -= sizeof( unsigned );
		}
		else {
			if( numbytes) fwrite( &rnum, 1, numbytes, stdout );
			exit( 0 );
		}
	}
}

