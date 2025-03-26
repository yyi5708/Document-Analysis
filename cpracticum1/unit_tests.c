// unit_tests.c
// Larry Kiser September 30, 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "cpracticum1.h"
#include "unit_tests.h"

// Simple boolean assert function for unit testing
int assert( int test_result, char error_format[], ... ) {
    va_list arguments ;
    static int test_number = 1 ;
    int result = 1 ;    // return 1 for test passed or 0 if failed
    
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
    int result ;
    
    printf( "\n----------------------- Test the fix_bad_code function ------------------------\n" ) ;
       
    // Test 1 --
    int numbers1[] = { 5, 10, 15, 20, 25 } ;

    result = fix_bad_code( numbers1, 2 ) ;
    assert( result == 15,
        "Expected 15 for sum of first two. Got %d", result )
        ? passcount++ : failcount++ ;

    // Test 2 -- 
    result = fix_bad_code( numbers1, 5 ) ;
    assert( result == 75,
        "Expected 75 for sum of first five. Got %d", result )
        ? passcount++ : failcount++ ;

    // Test 3 -- 
    result = fix_bad_code( numbers1, 0 ) ;
    assert( result == 0,
        "Expected 0 because entry count is 0 but got %d", result )
        ? passcount++ : failcount++ ;

    // Tests for count_spaces function
    printf( "\n----------------------- Test the count_spaces function -------------------------\n" ) ;
    
    // Test 4 -- 
    // If mystring[ start_index ] is an end of string then return 0.
    result = count_spaces( "", 0 ) ;
    assert( result == 0,
        "count_spaces must return 0 if start_index points to an end of string but it returned  %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 5 -- 
    // If mystring[ start_index ] has no spaces return 0
    result = count_spaces( "abcABC", 0 ) ;
    assert( result == 0,
        "count_spaces must return 0 if there are no spaces but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 6 -- 
    // If mystring[ start_index ] has one space then return a 1 as the count of spaces.
    result = count_spaces( " abc", 0 ) ;
    assert( result == 1,
        "count_spaces must return 1 since there is one space starting at index 0 but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 7 -- 
    // If mystring contains one  space but it is before start_index then return a 0.
    result = count_spaces( " abc", 1 ) ;
    assert( result == 0,
        "count_spaces must return 0 since start_index points to after the one space but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 8 -- 
    // Count the number of spaces in the string. Be sure to include the last one!
    result = count_spaces( "a b c  ", 0 ) ;
    assert( result == 4,
        "count_spaces must return 4 since there are 4 spaces but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    // Test 9 -- 
    // Count the number of spaces in the string but start at 'c'.  Be sure to include the last one!
    result = count_spaces( "a b c  ", 4 ) ;
    assert( result == 2,
        "count_spaces must return 2 since there are 2 spaces after the 'c' but it returned %d", result )
        ? passcount++ : failcount++ ;
        
    
    // Test replace_commas function
    printf( "\n----------------------- Test the replace_commas function ---------------------\n" ) ;
    
    // Test 10 --
    // If mystring is an empty string return a 0.
    // Make no change to the empty mystring.
	// create an empty string with extra space to reduce risk of crashes due to programming errors
	char test_string[5] = {'\0', '\0', '\0', '\0', '\0'} ;	

    result = replace_commas( test_string ) ;
    assert( result == 0,
        "replace_commas must return 0 on an empty string but it returned %d", result )
        ? passcount++ : failcount++ ;
        
	// Test 11 --
	// Make sure that empty_string was not corrupted by replace_commas
	result = 0 ; // default to success
	for ( int i = 0 ; i < 5 ; i++ )
		if ( test_string[i] != '\0' )
			result = -1 ;		// indicate corruption!
    assert( result == 0,
        "replace_commas must not alter empty_string!" )
        ? passcount++ : failcount++ ;

    // Test 12 -- 
	// Verify that an array with one comma is changed to a space
	test_string[0] = ',' ;	// test string now has one comma
    result = replace_commas( test_string ) ;
    assert( result == 1,
        "replace_commas must return 1 because there is one comma but it returned %d", result )
        ? passcount++ : failcount++ ;
        
	// Test 13 --
	// Verify that test_string now has a single space at the first position and rest is not corrupted
	result = 0 ;	// default to success
    for ( int i = 1 ; i < 5 ; i++ ) 
		if ( test_string[i] != '\0' )
			result = -1 ;
	if ( test_string[0] != ' ' )
			result = -2 ;
    assert( result == 0,
        "replace_commas did not correctly update test_string. -1 means corrupted array, -2 means first char not a space %d", result ) 
        ? passcount++ : failcount++ ;
        
    // Test 14 -- 
    // Verify that a string with multiple commas has all of its commas converted to spaces.
    char commas[] = "a,b,c," ;
    result = replace_commas( commas ) ;
	int compare = strcmp( commas, "a b c " ) ;
    assert( compare == 0,
        "replace_commas must update the string in 3 places. The new string should be \"%s\" but it returned \"%s\"", "a b c ", commas )
        ? passcount++ : failcount++ ;
        
	// Test 15 --
	// Verify that the previous call to replace commas returned a 3 because the string has 3 commas.
    assert( result == 3,
        "replace_commas must return 3 because the string has 3 commas but it returned %d", result )
        ? passcount++ : failcount++ ;
        
	// Test 16 --
	// Now test for no commas but one space in the string.
	char only_space[] = { '1', '2', ' ', '\0' } ;
	result = replace_commas( only_space ) ;
    assert( result == 1,
        "replace_commas must return 1 because the string has 1 space but no commas %d", result )
        ? passcount++ : failcount++ ;
        
    // Test get_char_at_position function
    printf( "\n----------------------- Test the get_char_at_position function ---------------\n" ) ;
    
	// Test 17 --
	// Return first character in the array
	char found_char = '\0' ;

    found_char = get_char_at_position( "first test", 0 ) ;
    assert( found_char  == 'f',
        "Expected 'f' (first character) but got \'%c\'", found_char )
        ? passcount++ : failcount++ ;
        
	// Test 18 --
	// Return the last character in the array
	found_char = '\0' ;
    found_char = get_char_at_position( "last one", 7 ) ;
    assert( found_char  == 'e',
        "Expected 'e' (last character)  but got \'%c\'", found_char )
        ? passcount++ : failcount++ ;
        
	// Test 19 --
	// return '?' because the position is one past the end of the array
	char test_array[] = { 'o', 'v', 'e', 'r', '\0', 'B', 'A', 'D' } ;
    found_char = get_char_at_position( test_array, 5 ) ; assert( found_char  == '?',
        "Expected '?' (past end of string but got \'%c\' with ASCII value %d", found_char, (int)found_char )
        ? passcount++ : failcount++  ;
        
    

    printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
    
    return failcount ;
}
