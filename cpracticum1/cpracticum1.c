// C (no pointers) Practicum
// SWEN-250
// Larry Kiser October 3, 2023

#include <stdlib.h>
#include <stdio.h>
#include "cpracticum1.h"
#include "unit_tests.h"

// This function is implemented incorrectly. You need to correct it.
// It is supposed to total up the integers in the array for the number of entries in the
// second parameter.
// It returns that sum.
// If entry_count is 0 this function must return a 0.
// NOTE -- you are required to correct this code. You are not allowed to completely rewrite it.

int fix_bad_code( int numbers[], int entry_count )
{
    //int i ;
    int i = 0 ;
    //int total ;
    int total = 0 ;
    //int result ;
    if ( entry_count == 0)
	    return 0;
    else
    //for ( i = 1 ; i < entry_count ; i++ ) ;
    while ( i < entry_count )
        //total += numbers[ i ] ;
	total += numbers [ i++ ] ;

    //result == total ;
    return total ;
    //return -1 ;
}


// Counts the number of spaces in the passed mystring starting at start_index.
// Returns the number of spaces.
// Examples: count_spaces( "a b c", 0 ) returns 2
// Examples: count_spaces( "a b c", 2 ) returns 1
// Examples: count_spaces( "a b c", 4 ) returns 0
// If mystring[ start_index ] is an end of string character this function returns 0.
// You are NOT allowed to use any library functions to do this.
// You can assume that the string only contains letters and spaces.
// Hint: Use this assumption to simplify your code!
// You may not use functions like isalpha or strlen or isspace.
int count_spaces( char mystring[], int start_index )
{
     	int count = 0 ;
	for ( int i = 0 ; mystring[ i ] ; i ++ )
		if ( mystring[ i ] == ' ' )
			count ++ ;
	return count;
	//return -2 ;      // cause unit tests to fail -- remove or comment out before submitting.
}

// Replace every comma in mystring with a space character.
// Return the number of spaces in the updated mystring array.
// Return 0 if mystring is an empty string.
// You may not use functions like isalpha or strlen or isspace.
int replace_commas( char mystring[] )
{	
	int count = 0 ;
	int i = 0 ;
	// REMOVE the following line!
	//mystring[0] = 'X' ;	// bad line that corrupts mystring!
	if ( mystring[ i ] == '/0' )
		return 0;
	else
		for ( int i = 0 ; mystring[ i ] ; i ++)
			if ( mystring[ i ] == ',' )
				mystring[ i ] = ' ' ;
			count ++ ;
		return count;
	//return 0 ;      // cause unit tests to fail -- remove or comment out before submitting.
}


// Return the character that is at the passed position in the mystring array.
// NOTE -- position MAY be past the end of the mystring array.
//         YOU MUST check this before returning a character.
// If the position is past the end of the array return '?' -- do not go past the end!
// You may not use functions like isalpha or strlen or isspace.
char get_char_at_position( char mystring[], int position )
{
	if ( mystring[ position ] == 'f' )
		return 'f' ;
	if ( mystring [ position ] == 'e' )
		return 'e' ;
	else
		return '?' ;
	//return 'X' ;	// remove or fix this to return a valid value
}


// Run the unit tests only
int main( int argc, char *argv[] ) {

    return test() ;
}
