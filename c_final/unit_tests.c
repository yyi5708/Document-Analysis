// C pointers final practicum
// SWEN-250
// unit_tests
// Larry Kiser updated December 8, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "c_final.h"
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
int test( int all )	// if all is true do the free unit tests at the end
{
	int passcount = 0 ;
	int failcount = 0 ;
	
	printf( "\nTests for insert_second_string.................\n" ) ;

	// Test 1
	assert( insert_second_string( NULL, "a" )  == NULL,
		"Expected NULL because pfirst is NULL" )
		? passcount++ : failcount++ ;

	// Test 2 
	assert( insert_second_string( "b", NULL ) == NULL,
		"Expected NULL because psecond is NULL" )
		? passcount++ : failcount++ ;

	// Test 3
	char *ptest3 = insert_second_string( "one ", "two" ) ;
	int good_pointer = ( ptest3 != NULL && ptest3 != BOGUS_POINTER ) ;
	assert( good_pointer,
		"Expected valid pointer but but it is NULL or BOGUS_POINTER" )
		? passcount++ : failcount++ ;

	// Test 4 
	if ( ! good_pointer )
	{
		assert( 0,
			 "Skipping test 4 due to bad pointer from test 3" ) ;
		failcount++ ;
	}
	else
		assert( strcmp( ptest3, "otwone " ) == 0,
			"Expected \"otwne o\" but got \"%s\"", ptest3 )
		? passcount++ : failcount++ ;
	
	printf( "\nTests for create_string.........................\n" ) ;
	
	// Test 5
	struct specs spec1 = { 0, 'A', BOGUS_POINTER } ;
	assert( create_string( NULL ) == 0,
		"Expect 0 since the struct spec pointer is NULL" )
		? passcount++ : failcount++ ;
	// Test 6
	assert( create_string( &spec1 ) == 1,
		"Expect 1 since the struct spec pointer is valid" )
		? passcount++ : failcount++ ;
	// Test 7 
	assert( spec1.p_new_string != BOGUS_POINTER,
		"p_new_string is a BOGUS POINTER -- expect valid_pointer with an empty string" )
		? passcount++ : failcount++ ;
	// Test 8
	if ( spec1.p_new_string != BOGUS_POINTER )
	{
		assert( strlen( spec1.p_new_string ) == 0 ,
			"Expect p_new_string to contain an empty string but got %s", spec1.p_new_string )
			? passcount++ : failcount++ ;
	}
	else
		assert( 0, "skipping test 8 due to bogus pointer" ) ? passcount++ : failcount++ ;
	// Test 9 
	struct specs spec2 = { 3, 'B', BOGUS_POINTER } ;
	assert( create_string( &spec2 ) == 1,
		"Expect return status of 1 because spec2 is valid" )
		? passcount++ : failcount++ ;
	// Test 10
	assert( spec2.p_new_string != BOGUS_POINTER && strcmp( spec2.p_new_string, "BBB" ) == 0,
		"Expect p_new_string to not be the BOGUS_POINTER and expect BBB" )
		? passcount++ : failcount++ ;
		if ( spec2.p_new_string != BOGUS_POINTER && strcmp( spec2.p_new_string, "BBB" ) != 0 )
			printf( "but got %s\n", spec2.p_new_string ) ;
	// Test 10
//	struct specs spec2 ;
//	memset( &spec2, 0xff, sizeof(spec2) ) ;	// fill with bad values
//	spec2.string_copy = BOGUS_POINTER ;		// use standard bogus pointer
//	char *teststring = "12 aaBbff9" ;
//	assert( create_string( teststring, &spec2 ) == 1,
//		"Expect 1 since both parameters are not NULL" )
//		? passcount++ : failcount++ ;
	// Test 11
//	assert( spec2.upper_case_count == 1 && spec2.lower_case_count == 5 &&
//			spec2.digits_count == 3,
//		"Expect upper 1, lower 5, digits 3 but got upper %d, lower %d, digits %d",
//		spec2.upper_case_count, spec2.lower_case_count, spec2.digits_count )
//		? passcount++ : failcount++ ;
	// Test 12
//	if ( spec2.string_copy == BOGUS_POINTER )
//	{
//		assert( 0,
//			 "Skipping Test 12 because string_copy is a BOGUS_POINTER" ) ;
//		failcount++ ;
//	}
//	else
//		assert( spec2.string_copy != BOGUS_POINTER && strcmp( spec2.string_copy, teststring ) == 0,
//		"Expect string_copy to not be the BOGUS_POINTER and expect it to be \"%s\" but got \"%s\"",
//			teststring, spec2.string_copy )
//		? passcount++ : failcount++ ;

	printf( "\nTests for divide_by_two...........................\n" ) ;
	// Test 13
	int result = 0 ;
	result = divide_by_two( NULL, 5 ) ;
	assert( result == BAD_PARAMETERS,
		"Expect BAD_PARAMETERS because p_integers is NULL but got %d", result )
		? passcount++ : failcount++ ;
	// Test 14
	int array1[] = { 0, 1 } ;
	result = divide_by_two( array1, 0 ) ;
	assert( result == BAD_PARAMETERS,
		"Expect BAD_PARAMETERS because number of integers is 0 but got %d", result )
		? passcount++ : failcount++ ;
	// Test 15
	result = divide_by_two( array1, -1 ) ;
	assert( result == BAD_PARAMETERS,
		"Expect BAD_PARAMETERS because number of integers is -1 but got %d", result )
		? passcount++ : failcount++ ;
	// Test 16
	result = divide_by_two( array1, 2 ) ;
	assert( result == 0,
		"Expect sum of 0 because 0 and 1 divided by 2 are both 0 but got %d", result )
		? passcount++ : failcount++ ;
	// Test
	assert( array1[0] == 0 && array1[1] == 0,
		"Expect array1[0] and array1[1] to be both 0 but got %d, %d", array1[0], array1[1] )
		? passcount++ : failcount++ ;

	// Test 17
	int array2[] = { 3, 8, 6, 1, 44, 99 } ;
	int array2_div2[] = { 1, 4, 3, 0, 22, 99 } ;	// only divide and sum the first 5
	result = divide_by_two( array2, 5 ) ;
	int compare = memcmp( array2, array2_div2, sizeof(array2) ) ;
	assert( compare == 0,
		"Expect array to be 1, 4, 3, 0, 22 with the 99 unchanged but got %d %d %d %d %d %d",
			array2[0], array2[1], array2[2], array2[3], array2[4], array2[5] )
		? passcount++ : failcount++ ;
	// Test
	assert( result == 30,
		"Expect 30 because 1+4+3+0+22 is 30 but got %d", result )
		? passcount++ : failcount++ ;

	printf( "\nTests for get_bit ...................................\n" ) ;
	// Test 22
	result = get_bit( 0, 0 ) ;
	assert( result == 0,
		"Expect 0 because value and position are both 0 but got %d", result )
		? passcount++ : failcount++ ;

	// Test 22
	result = get_bit( 8, 2 ) ;
	assert( result == 0,
		"Expect 0 because bit position 2 in the value 8 is 0 but got %d", result )
		? passcount++ : failcount++ ;

	// Test 22
	result = get_bit( 8, 3 ) ;
	assert( result == 1,
		"Expect 1 because bit position 3 in the value 8 is 1 but got %d", result )
		? passcount++ : failcount++ ;

	// Test 22
	result = get_bit( 8, 4 ) ;
	assert( result == 0,
		"Expect 0 because bit position 4 in the value 8 is 0 but got %d", result )
		? passcount++ : failcount++ ;

	// NOTE -- if this is crashing it is because of an error in your implementation in 
	//         create_string or insert_second_string.
	//         If you cannot figure out what to do change
	//         your code to always return NULL.
	if ( all )
	{
		printf( "\nNow freeing pointers created during prior unit tests\n" ) ;

		if ( good_pointer )
		{
			free( ptest3 ) ;
			passcount++ ;
			printf( "\nsuccessful free of string from insert_second_string\n" ) ;
		}
		else
			assert( 0, "skipping free from insert_second_string due to bad pointer" ) ? passcount++ : failcount++ ;
			
		if ( spec1.p_new_string != BOGUS_POINTER )
		{
			free( spec1.p_new_string ) ;	// free empty string returned from create_string
			printf( "\nfirst free of string from create_string successful\n" ) ;
			passcount++ ;
		}
		else
			assert( 0, "skipping free from first create_string due to bad pointer" ) ? passcount++ : failcount++ ;

		if ( spec2.p_new_string != BOGUS_POINTER )
		{
			free( spec2.p_new_string ) ;	// free empty string returned from create_string
			printf( "\nsecond free of string from create_string successful\n" ) ;
			passcount++ ;
		}
		else
			assert( 0, "skipping free from second create_string due to bad pointer" ) ? passcount++ : failcount++ ;
	}
	else
		printf( "\nSKIPPING free unit tests\n" ) ;

	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
