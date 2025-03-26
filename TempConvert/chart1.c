#include <stdio.h>
int main()
{
printf("Fahrenheit-Celsius\n");
int Fahrenheit;
int Celsius;
for (Fahrenheit = 0; Fahrenheit <= 300; Fahrenheit += 20)
{
int Celsius = 5 * (Fahrenheit - 32) / 9;
printf("%5d%13d\n", Fahrenheit, Celsius);
}
return 0;
}
