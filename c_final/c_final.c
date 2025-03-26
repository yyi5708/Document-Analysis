// C pointers final practicum 
// SWEN-250 Fall 2023
// Larry Kiser December 13, 2023

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "c_final.h"
#include "unit_tests.h"

// returns 0 if the bit at the bit_position in value is not set.
// returns 1 if the bit at the bit_position in value is set.
// Note that bit_position is a number of 0 through 31 inclusive.
// The bit_position will always be from 0 through 31.
// Examples: value is 7 and bit_position is 2 -- returns 1
//           value is 7 and bit_position is 5 -- returns 0

int get_bit(unsigned int value, int bit_position) 
{
	return ((value & (1 << bit_position)) != 0);
}

// Return a NULL pointer if pfirst or psecond is a NULL pointer..
//
// The purpose of this function is to create a new string that
// contains the first character from pfirst, all of the characters
// in psecond followed by the rest of the characters in pfirst.
//
// You can assume that pfirst has at least two characters and
// that psecond has at least one character.
//
// You return this malloc'ed string.
//
// NOTE -- you must malloc exactly the amount of space needed to
// store all of the characters in both strings.
//
// Example: pfirst is "start " and psecond is "end". You will
// create a new string containing "sendtart ". You return a pointer to
// this new string.
//
// You are allowed to use functions like strlen and strcat.
// PRO TIP: remember that malloc returns uninitialized data!
//
// Parameters:
//		*pfirst is a character pointer to first string to copy to your new string.
//		*psecond s a character pointer to second string to copied to right after 
//          first character from pfirst.

char *insert_second_string(char *pfirst, char *psecond)
{
    	if (pfirst == NULL || psecond == NULL)
    	{
    	return NULL;
    	}
	size_t len_first = strlen(pfirst);
	size_t len_second = strlen(psecond);
	size_t len_total = len_first + len_second + 1;
	char *result = (char*)malloc(len_total);
    	if (result != NULL)
    	{
    	strcpy(result, pfirst);
    	strcat(result, psecond);
    	}
    	return result;
}

// First checks that the pointer to the passed structure is not NULL.
// Returns 0 if the passed struct pointer is NULL.
// Returns 1 if the passed struct pointer is not NULL
//
// NOTE -- the struct definition is in c_final.h -- refer to that struct!
// First malloc exactly enough space to hold the requested number_of_letters.
// Create a neiw string contains number_of_letters of the letter in the struct.
// if number_of_letters is 0 then create an empty string that you malloc'ed.
// Assign your malloc'ed pointer to the p_new_string pointer in struct spec.
// You must malloc the minimum size on the heap to create the new string.

int create_string(struct specs *p_specs)
{
    	if (p_specs == NULL)
    	{
        return 0;
    	}
    	p_specs->p_new_string = (char*)malloc((p_specs->number_of_letters + 1));
    	if (p_specs->p_new_string == NULL)
    	{
        return 0;
   	}
    	memset(p_specs->p_new_string, p_specs->letter, p_specs->number_of_letters);
    	return 1;
}

// p_integers points to an array of integers.
// number_of_integers specifies the length of this array.
// if p_integers is a NULL pointer return BAD_PARAMETERS (defined in c_final.h)
// if number_of_integers is zero or negative return BAD_PARAMETERS
// if both parameters are valid divide every integer in the array by 2.
// Return the sum of all of the integers after they are divided by 2.

int divide_by_two(int *p_integers, int number_of_integers)
{
    	if (p_integers == NULL || number_of_integers <= 0)
    	{
        return BAD_PARAMETERS;
    	}
    	int sum = 0;
    	for (int i = 0; i < number_of_integers; i += 1)
    	{
        p_integers[i] /= 2;
        sum += p_integers[i];
    	}
    	return sum;
}

