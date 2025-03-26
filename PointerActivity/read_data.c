/*
* 	Implementation of the read_data module.
* 	See read_data.h for a description of the read_data function's specification.
* 	Note that the parameter declarations in this module must be
* 	compatible with those in the read_data.h header file.
*	Reads the three fields from lines such as W$1349$1.414$ into
*	local variables using getchar().
*	Converts the two numeric fields to numbers using atoi for the
*	integer fields and atof for the double.
*	Using a correctly defined set of parameters (use pointers) pass
*	those values back to the program that called this function.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read_data.h"

void read_data(char *c, int *i, double *d)
{
scanf("%c$", c);
scanf("%d$", i);
scanf("%lf$", d);
}

