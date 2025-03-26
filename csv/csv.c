//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "csv.h"
#include "unit_tests.h"
//
bool is_end_of_field(int ch)
{
return (ch == ',') || (ch == '\n') || (ch == EOF) || (ch == '\r');
}
//
int min(int x, int y)
{
return x < y ? x : y;
}
//
int get_field(f_string field)
{
int c;
int i = 0;
while ((c = getchar()) != EOF && !is_end_of_field(c))
{
if (i < MAX_CHARS)
{
field[i ++] = c;
}
}
field[min(i, MAX_CHARS)] = '\0';
return c;
}
//
csv_line get_line()
{
csv_line line;
int c;
line.nfields = 0;
while ((c = get_field(line.field[line.nfields])) != EOF)
{
line.nfields ++;
if  (c == '\n')
{
break;
}
}
return line;
}
//
void print_csv(csv_line header, csv_line data)
{
int fields = min(header.nfields, data.nfields);
for (int i = 0; i < fields; i ++)
{
printf("%s = %s\n", header.field[i], data.field[i]);
}
}
//
int main(int argc, char *argv[])
{
csv_line header;
csv_line current;
if (strstr(argv[0], "test"))
return test();
header = get_line();
current = get_line();
while (current.nfields > 0)
{
print_csv(header, current);
current = get_line();
}
return 0 ;
}
//
