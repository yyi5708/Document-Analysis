// main program for the Document Analysis Project
// Revised Mar. 3, 2018 to use Part 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "unit_tests.h"

// Selects linked list tests, analysis tests, or both
static int test_choice( char *test_set )
{
	char selection = tolower( *test_set ) ;
	int fail_count = 0 ;
	
	switch ( selection )	// just check the first letter
	{
		case 't' :
			fail_count = test_linked_list_functions() ;
			reset_test_counter() ;
			fail_count += test_analysis() ;
			reset_test_counter() ;
			fail_count += test_student() ;
			break ;
		case 'l' :
			fail_count = test_linked_list_functions() ;
			break ;
		case 'a' :
			fail_count = test_analysis() ;
			break ;
		case 's' :
			fail_count = test_student() ;
			break ;
			
	}
	return fail_count ;
}


// If you run analysis with no parameters then it will run all tests (linked list, analysis, and student)
//     ./test
//
// If you run it this way:
//     ./test linked (l is sufficient)
// you will just run the tests of your linked_list_function code from Part 1.
//
// If you run it this way:
//     ./test analysis (a is sufficient)
// you will just run the part2 tests of your analysis.c code.
//
// If you run it this way:
//      ./test student (s is sufficient)
// you will just run your student created unit tests along with the two provided tests in unit_tests_student.c
//
int main( int argc, char *argv[] ) {
	char *test_set = "t" ;			// default to running all tests.
	
	if ( argc > 1 )					// if not running all tests then point to the desired test set.
		test_set = argv[1] ;
	
	int fail_count = test_choice( test_set ) ;
	printf( "\nTotal failures %d\n", fail_count ) ;
	
	return fail_count ;
}
