// C pointers Practicum2
// SWEN-250
// unit_tests
// Larry Kiser updated November 14, 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "cpracticum2.h"
#include "unit_tests.h"

// Simple boolean assert function for unit testing
int assert( int test_result, char error_format[], ... ) {
	va_list arguments ;
	static int test_number = 1 ;
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

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// do the unit tests
int test()
{
	int passcount = 0 ;
	int failcount = 0 ;
	
	printf( "\nTests for sum_integer_array........................\n" ) ;

	// Test 1
	int array1[] = { -999, 3222 } ;
	assert( sum_integer_array( array1 ) == 0,
		"#1 Expected '0' because array1 starts with -999" )
		? passcount++ : failcount++ ;
	// Test 2 
	int array2[] = { 5, -999, 1050 } ;
	assert( sum_integer_array( array2 ) == 5,
		"#2 Expected 5 because there is only one entry of 5 before the seeing the -999 value" )
		? passcount++ : failcount++ ;

	// Test 3
	int array3[] = { 5, 10, 15, 20, 25, 230, 335, 440, -998, -999, -1000 } ;
	int value = sum_integer_array( array3 ) ;
	assert( value == 82,
		"#3 Expected 82 because sum of the values through the -998 is 82 but got %d", value )
		? passcount++ : failcount++ ;

	// Test 4 
	int *p_array = NULL ;
	int result = sum_integer_array( p_array ) ;
	assert( result == -1,
		"#4 Expected -1 because we passed a NULL pointer but got %d", result )
		? passcount++ : failcount++ ;
	
	printf( "\nTests for count_occurrences.........................\n" ) ;
	
	// Test 5
	char *teststring = "9GRR3" ;
	result = count_occurrences( teststring, '9' ) ;
	assert( result == 1,
		"#5 Expect 1 because there is one 9 in the string but got %d", result )
		? passcount++ : failcount++ ;
	// Test 6
	result = count_occurrences( teststring, 'A' ) ;
	assert( result == 0,
		"#6 Expect 0 because this string does not have an A but got %d", result )
		? passcount++ : failcount++ ;
	// Test 7 
	result = count_occurrences( teststring, '3' ) ;
	assert( result == 1,
		"#7 Expect 1 because there is one 3 in the string but got %d", result )
		? passcount++ : failcount++ ;
	// Test 8
	result = count_occurrences( teststring, 'R' ) ;
	assert( result == 2,
		"#8 Expect 2 because there are two R letters in this string but got %d", result )
		? passcount++ : failcount++ ;
		
	printf( "\nTests for compare_pointers..........................\n" ) ;
	// Test 9
	char array[] = "GGHHIJK" ;
	char letter = 'X' ; // init to bogus return letter
	letter = compare_pointers( &array[5], &array[5] ) ;
	assert( letter == 'S',
		"#9 Expect S for the same location but got %c", letter )
		? passcount++ : failcount++ ;
	// Test 10
	letter = compare_pointers( &array[3], &array[2] ) ;
	assert( letter == 'B',
		"#10 Expect B for p_second before p_first but got %c", letter )
		? passcount++ : failcount++ ;
	// Test 11
	letter = compare_pointers( &array[1], &array[2] ) ;
	assert( letter == 'A',
		"#11 Expect A for p_second after p_first but got %c", letter )
		? passcount++ : failcount++ ;
	// Test 12
	letter = compare_pointers( &array[5], &array[2] ) ;
	assert( letter == '?',
		"#12 Expect ? for some other non-adjacent positions but got %c", letter )
		? passcount++ : failcount++ ;
		
	printf( "\nTests for fix_bad_code..............................\n" ) ;
	// Test 13
	char fix_array[] = "00ancde" ;
	char *p_last_one = fix_bad_code( fix_array, 'e' ) ;
	assert( p_last_one == &fix_array[6],
		"#13 Expect a pointer to the 7th character in the array but got position %d", (int)(p_last_one - fix_array) )
		? passcount++ : failcount++ ;
	// Test 14
	p_last_one = fix_bad_code( fix_array, '0' ) ;
	assert( p_last_one == &fix_array[1],
		"#14 Expect a pointer to the 2nd character in the array but got position %d", (int)(p_last_one - fix_array) )
		? passcount++ : failcount++ ;
	// Test 15
	char fix2_array[] = "0abcdefgh00" ;
	p_last_one = fix_bad_code( fix2_array, '0' ) ;
	assert( p_last_one == &fix2_array[10],
		"#15 Expect a pointer to the 11th character in the array but got position %d", (int)(p_last_one - fix2_array) )
		? passcount++ : failcount++ ;
		
	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
