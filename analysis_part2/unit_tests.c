// unit_tests.c
// Larry L. Kiser Oct. 22, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "unit_tests.h"

static int test_number = 1 ;	// hide this from outside world

// reset test number function to allow independent sets of unit tests.
void reset_test_counter( void )
{
	test_number = 1 ;
}


// Simple boolean assert function for unit testing
// DO NOT MODIFY THIS FUNCTION
int assert( int test_result, char error_format[], ... ) {
	va_list arguments ;
	int result = 1 ;	// return 1 for test passed or 0 if failed
	
	if ( ! test_result ) {
		va_start( arguments, error_format ) ;
		printf( "Test # %d failed: ", test_number ) ;
		vprintf( error_format, arguments ) ;
		printf( "\n" ) ;
		result = 0 ;
	}
	test_number++ ;
	return result ;
}
