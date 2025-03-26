// C pointers light Practice Practicum
// SWEN-250
// Larry Kiser October 30, 2015

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unit_tests.h"

// Run the unit tests or as a "normal program".
int main( int argc, char *argv[] )
{

	// Execute unit tests if program name contains "test".
	if ( strstr( argv[0], "test" ) )
		return test() ;

	printf( "\nDoes nothing -- please run unit tests instead.\n\n" ) ;
	
	return 0 ;
}
