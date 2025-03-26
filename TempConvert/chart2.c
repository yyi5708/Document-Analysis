#include <stdio.h>
int main()
{
printf("Fahrenheit-Celsius\n");
float Fahrenheit;
float Celsius;
for (Fahrenheit = 0.0; Fahrenheit <= 300.0; Fahrenheit += 20.0)
{
float Celsius = (5.0 / 9.0) * (Fahrenheit - 32.0);
printf("%5.0f%13.1f\n", Fahrenheit, Celsius);
}
return 0;
}
