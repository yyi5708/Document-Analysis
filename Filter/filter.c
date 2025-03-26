//

#include <stdlib.h>

#include <string.h>

#include <stdbool.h>

#include "filter.h"

#define NUL ('\0')

static bool includes(char c, char *s)
{
while(*s && c != *s) 
{
s += 1;
}
return c == *s;
}

static bool prefix(char *s, char *pre)
{
while(*pre && *s == *pre)
{
s += 1;
pre += 1;
}
return *pre == NUL;
}

void filter_ch_index(char string[], char result[], char ch)
{
int i = 0;
int j = 0;
while (string[i] != NUL)
{
if (string[i] != ch)
{
result[j] = string[i];
j += 1;
}
i += 1;
}
result[j] = NUL;
}

char *filter_ch_ptr(char *string, char ch)
{
char *result = malloc(strlen(string) + 1);
char *p = result;
while (*string != NUL)
{
if (*string != ch)
{
*p = *string;
p += 1;
}
string += 1;
}
*p = NUL;
return result;
}

void filter_any_index(char string[], char result[], char remove[])
{
int i = 0;
int j = 0;  
while (string[i] != NUL)
{
if (!includes(string[i], remove))
{
result[j] = string[i];
j += 1;
}
i += 1;
}    
result[j] = NUL;
}

char *filter_any_ptr(char *string, char* remove)
{
char *result = malloc(strlen(string) + 1);
char *p = result;
while (*string != NUL)
{
if (!includes(*string, remove))
{
*p = *string;
p += 1;
}
string += 1;
}
*p = NUL;
return result;
}

char *filter_substr(char *string, char* substr)
{
char *result = malloc(strlen(string) + 1);
char *p = result;
while (*string != NUL)
{
if (prefix(string, substr))
{
string += strlen(substr);
}
else
{
*p = *string;
p += 1;
string += 1;
}
}    
*p = NUL;
return result;
}

//
