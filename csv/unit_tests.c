// unit_tests.c
// Larry L. Kiser Oct. 22, 2015
// Copyright 2015 All Rights Reserved

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>


#include "csv.h"

// used by stdout switching functions
static int stdout_file_descriptor = 0 ;
static fpos_t stdout_position ;

// Redirect printf's to the specified text file (redirect stdout).
static void switch_stdout_to_file( char *filename )
{
    fflush( stdout ) ;
    fgetpos( stdout, &stdout_position ) ;
    stdout_file_descriptor = dup( fileno( stdout ) ) ;
    freopen( filename, "w", stdout ) ;
}

// Restore normal printf behavior (restore stdout).
// MUST be called only after a prior call to switch_stdout_to_file!
static void restore_stdout( void )
{
    if ( stdout_file_descriptor )
    {
        fflush( stdout ) ;
        dup2( stdout_file_descriptor, fileno( stdout ) ) ;
        close( stdout_file_descriptor ) ;
        clearerr( stdout ) ;
        fsetpos( stdout, &stdout_position ) ;
    }
}

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

// First make sure the get_field function is implemented properly.
// Reads and checks the first three fields from the first line in food.csv.
void test_get_field( int *passcount, int *failcount )
{
	int result ;
	f_string one_field ;

	// This redirects stdin to use the test files we want
	freopen( "food.csv", "r", stdin ) ;
	
	// 1. See if we can read the first field from food.csv
	result = get_field( one_field ) ;
	assert( !strcmp( one_field, "Food" ),
		"Read first field failed. Expected: Food  Actual: %s", one_field )
		? (*passcount)++ : (*failcount)++ ;
	// 2. Did we get a comma returned from get_field?
	assert( ',' == result,
		"Wrong character returned from get_field. Expected: ,  Actual: %c", result )
		? (*passcount)++ : (*failcount)++ ;
	
	// 3. See if we can read the second field from food.csv
	result = get_field( one_field ) ;
	assert( !strcmp( one_field, "Amount" ),
		"Read second field failed. Expected: Amount  Actual: %s", one_field )
		? (*passcount)++ : (*failcount)++ ;
	// 4. Did we get a comma returned from get_field?
	assert( ',' == result,
		"Wrong character returned from get_field. Expected: ,  Actual: %c", result )
		? (*passcount)++ : (*failcount)++ ;
	
	// 5. See if we can read the third field from food.csv
	result = get_field( one_field ) ;
	assert( !strcmp( one_field, "Calories" ),
		"Read third field failed. Expected: Calories  Actual: %s", one_field )
		? (*passcount)++ : (*failcount)++ ;
	// 6. Did we get a newline returned from get_field?
	assert( '\n' == result,
		"Wrong character returned from get_field. Expected: 0x0a  Actual: 0x%02x", result )
		? (*passcount)++ : (*failcount)++ ;
}

// Test the get_line function by reading the second line from food.csv.
// Verify that we got 3 fields with the correct text.
void test_get_line( int *passcount, int *failcount )
{
	csv_line one_line ;

	// 7. read the second line in the file: Peanut Butter,tbsp,95 and see if we have 3 fields
	one_line = get_line() ;
	assert( one_line.nfields == 3,
		"Read second line. Expected: 3 fields  Actual: %d", one_line.nfields )
		? (*passcount)++ : (*failcount)++ ;
	// 8. see if first field is Peanut Butter
	assert( !strcmp( one_line.field[0], "Peanut Butter" ),
		"Read second line. Expected first field: Peanut Butter  Actual: %s", one_line.field[0] )
		? (*passcount)++ : (*failcount)++ ;
	// 9. see if second field is tbsp
	assert( !strcmp( one_line.field[1], "tbsp" ),
		"Read second line. Expected second field: tbsp  Actual: %s", one_line.field[1] )
		? (*passcount)++ : (*failcount)++ ;
	// 10. see if third field is 95
	assert( !strcmp( one_line.field[2], "95" ),
		"Read second line. Expected third field: 95  Actual: %s", one_line.field[2] )
		? (*passcount)++ : (*failcount)++ ;
}

// Tests print_csv function by redirecting printf to a text file.
// We then use a system call to execute the linux diff utility. That
// utility returns non-zero if there is a difference or failure to compare the two files.
// Note that you must have the file expected_print_csv.out in your current directory.
// WARNING -- if you add any printfs to this test function you will probably cause it to fail!
void test_print_csv( int *passcount, int *failcount )
{
	int result ;
	csv_line one_line_with_3 = { 3, { "a", "b", "c" } } ;
	csv_line one_line_with_4 = { 4, { "d", "e", "f", "g" } } ;
	csv_line one_line_with_5 = { 5, { "s", "t", "u", "v", "w" } }  ;
	csv_line header_line_with_4 = { 4, { "Col 1", "Col 2", "Col 3", "Col 4" } }  ;

	// redirect stdout to a file so we can diff them
	switch_stdout_to_file( "print_csv.out" ) ;
	
	// 11. Test print with line of four (normal case of # of headers matches # of fields in the line).
	// Then test the two mismatches where the data line has one less and has one more.
	printf( "Test printing header line and data line when both have 4 fields\n" ) ;
	print_csv( header_line_with_4, one_line_with_4 ) ;
	
	printf( "Test printing when data line has only 3 fields\n" ) ;
	print_csv( header_line_with_4, one_line_with_3 ) ;
	
	printf( "Test printing when data line has 5 fields\n" ) ;
	print_csv( header_line_with_4, one_line_with_5 ) ;
	
	// restore stdout to normal
	restore_stdout() ;
	// Now run the diff utility to see if print_csv created the correct output for all three tests above.
	result = system( "diff print_csv.out expected_print_csv.out" ) ;
	assert( 0 == result,
		"Error in print_csv. See above diff utility results." )
		? (*passcount)++ : (*failcount)++ ;
}

// Main fucntion to call the unit tests.
int test()
{
	int passcount = 0 ;
	int failcount = 0 ;
	
	test_get_field( &passcount, &failcount ) ;
	test_get_line( &passcount, &failcount ) ;
	test_print_csv( &passcount, &failcount ) ;
	
	printf( "\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
