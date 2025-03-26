/*
*	Driver program for the activity.
*	1. Declares local variables for the character, integer, and 
*	   double precision values returned by read_data.
*	2. Calls read_data with pointers to the variables so that
* 	   the values read can be returned.
*	3. On return, prints the character, integer, and double
* 	   precision number using the following format string for
* 	   printf: "Character %c Integer %d Floating point %.4f\n"
* 	   Note: you must also, of course, provide the values to
* 	   be printed.
*	4. Return a 0 to the operating system.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "read_data.h"

static void helper_1(char *my_string)
{
char *work_ptr = my_string;
int length = strlen(my_string);
printf("\n%s and the size of that string %lu %lx\n", my_string, strlen(my_string), (unsigned long)(my_string));
for (int i = 0; i < length; i ++)
	printf("%c", *work_ptr ++);
printf("\n");
}

static void helper_2(char *my_string)
{
for (char *work_ptr = my_string; *work_ptr;)
	printf("%c", *work_ptr ++);
printf("\n");
}

static void helper_3(int *number)
{
printf("\n%d passed value\n", *number);
(*number) ++;
}

int main()
{
//char c;
//int i;
//double d;
//read_data(&c, &i, &d);
//printf("Character %c Integer %d Floating point %.4f\n", c, i, d);
int test_integer = 0x41;
helper_1("my_string_contents");
helper_2("send string stuff.");
helper_3(&test_integer);
printf(" \n%d\n", test_integer);
printf("\n");
return 0;
}

