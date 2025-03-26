#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
int tot_chars = 0;
int tot_lines = 0;
int tot_words = 0;
int in = 0;
int ch;
FILE *file;
file = fopen(argv[1], "r");
while ((ch = fgetc(file)) != EOF)
{
tot_chars += 1;
if (isspace(ch))
{
if (ch == '\n')
{
tot_lines += 1;
}
in = 0;
}
else
{
if (!in)
{
tot_words += 1;
in = 1;
}
}
}
printf(" %d  %d %d %s  \n ", tot_lines, tot_words, tot_chars, argv[1]);
fclose(file);
return 0;
}
