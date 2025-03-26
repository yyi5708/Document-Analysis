// C pointers final Practicum
// SWEN-250
// Larry Kiser December 8, 2021

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unit_tests.h"

int main(int arg_count, char *arg_strings[])
{
	int all = 0;		// default is skip the last unit tests to free the malloc'd space
	if (arg_count == 2 && !strcmp(arg_strings[1], "all"))
	all = 1 ;		// run all unit tests including the ones that free the heap space.
	return test(all);
}

