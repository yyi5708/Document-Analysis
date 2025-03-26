#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE (80)
extern int readline(char line[], int max);
extern void copy(char to[], char from[]);
extern int test(void);
int main(int argc, char *argv[])
{
int len;
char line[MAXLINE + 1];
int max_len = 0;
char longest_line[MAXLINE + 1];
if (strstr(argv[0], "test"))
return test();
while ((len = readline(line, MAXLINE )) > 0)
{
if (len > max_len)
{
max_len = len;
copy(longest_line, line);
}
printf("%s\n", line);
}
if (max_len > 0)
{
printf("%s\n", longest_line);
}
return 0;
}
int readline(char s[], int max_chars)
{
int length = 0;
int character;
while (length < max_chars - 1)
{
character = getchar();
if (character == EOF)
{
if (length == 0)
{
return -1;
}
break;
}
if (character == '\n')
{
break;
}
s[length] = (char)character;
length += 1;
}
s[length] = 0;
return length;
}
void copy(char to[], char from[])
{
int i = 0;
while ((to[i] = from[i]) != 0)
{
i += 1;
}
}
int assert(int testresult, char error_message[])
{
static int test_number = 1;
int result = 1;
if (!testresult)
{
printf("%d test failed: %s\n", test_number, error_message);
result = 0;
}
return result;
}
int test()
{
char output_array[MAXLINE + 1] = "";
char testline1[] = "A";
char testline2[] = "";	
char testline3[] = "Typical line to be copied.";
char testline4[] = "\n\n\n";
int passcount = 0;
int failcount = 0;
int result;
printf("\nExecuting unit tests\n");
copy(output_array, testline1);
if (assert(!strcmp(output_array, testline1), "Unit test for one character string"))
passcount += 1;
else
failcount += 1;	
copy(output_array, testline2);
if (assert(!strcmp(output_array, testline2), "Unit test for copying empty string"))
passcount += 1;
else
failcount += 1;
copy(output_array, testline3);
if (assert(!strcmp(output_array, testline3), "Unit test for typical string"))
passcount += 1;
else
failcount += 1;
copy(output_array, testline4);
if (assert(!strcmp(output_array, testline4 ), "Unit test for string with only newlines"))
passcount += 1;
else
failcount += 1;
printf("\nSummary of unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount);
return failcount;
}
