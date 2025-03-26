// C pointers practicum 2 
// SWEN-250 Fall Term
// Larry Kiser November 13, 2023

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cpracticum2.h"
#include "unit_tests.h"

// This function is implemented incorrectly. You need to correct it.
// When fixed it returns a pointer to the last occurrence of find_char
// in the passed p_string ;
// If find_char is not present anywhere in p_string it returns a NULL pointer.
// You can assume that p_string is a valid pointer to a string and that
// find_char is a normal letter or number.
//
// NOTE -- you are NOT allowed to use an index value in your solution.
//         You cannot use "pstring[index]" array syntax.
//

char *fix_bad_code(char *p_string, char find_char)
{
	static char bogus_array[] = "bogus0";
    	char *p_last_found = bogus_array;
    	char *p_work = p_string += 1;
    	p_last_found = NULL;
    	while (*p_work != '\0')
    	{
        if (*p_work == find_char)
        {
        p_last_found = p_work;
        }
        p_work += 1;
    	}
    	return (p_last_found == bogus_array) ? NULL : p_last_found;
}

// Return the sum of all of the integers in the array until you see a
// a value of exactly -999. Do not include the -999 in your sum.
// Test to confirm that the pass integer pointer p_integers is not NULL.
// If p_integers is NULL then return a -1.
//
// NOTE -- you are NOT allowed to use an index value in your solution.
//         You cannot use "pstring[index]" array syntax.
//
// Parameterj:
//		*p_integers is a a pointer to an array of integers that is terminated by
//			the value of exactly -999. NOTE -- p_integers may be a NULL pointer!
//

int sum_integer_array(int *p_integers)
{
	int sum = 0;
    	if (p_integers == NULL)
	{
        return -1;
    	}
    	while (*p_integers != -999)
	{
        sum += *p_integers;
        p_integers += 1;
   	}
    	return sum;
}

// Count the number of times that the letter count_this_char occurs 
// in the p_string that is passed to this function.
// Return this count. Note that this count may be zero!
//
// You can assume that count_this_char is a valid letter or number.
// You can assume that p_string is a valid pointer. You do not have to
// check for NULL.
//
// NOTE -- you are NOT allowed to use an index value in your solution.
//         You cannot uise "pstring[index]" array syntax.
//

int count_occurrences(char *p_string, char count_this_char)
{
	int count = 0;
	while (*p_string != '\0')
   	{
        if (*p_string == count_this_char)
        {
        count += 1;
        }
       	p_string += 1;
    	}
	return count;
}

// The two passed char pointers are pointing to the same string.
// One of four things is true:
//    They both point to the same position.
//        Return the letter 'S' for same.
//    p_second points to the letter after the letter pointed to by p_first.
//        Return the letter 'A' for after.
//    p_second points to the letter before the letter pointed to by p_first.
//        Return the letter 'B' for before.
//    if none of the previous three conditions is true:e
//        Return the letter '?' meaning unknown.
//
// NOTE -- you must compare the positions not the letters pointed to by these pointers.
//    Some of the test cases will have identical letters at adjacent positions.
//    Example string: "ABCDEEFF" -- if p_first points to the first E and p_second
//       points to the second E you would return a letter A for after.
//    

char compare_pointers( char *p_first, char *p_second )
{
	if (p_first == p_second)
	{
	return 'S';
	}
	if (p_first > p_second)
	{
	return 'B';
	}
	if (p_second > p_first)
	{
	return 'A';
	}
	else
	{
	return '?';
	}
}

