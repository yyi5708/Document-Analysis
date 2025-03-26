#include <stdio.h> // Include The Standard Input/Output Library.
int primes[15]; // Declare An Array To Store Prime Number Information.
int upper_bound; // Declare A Variable To Store The Upper Bound.
int i; // Declare A Loop Counter.
int j; // Declare A Variable For Inner Loop.
int k; // Declare A Variable To Check If A Number Is Prime.
void check_if_prime(int k, int primes[]) // Function To Check If A Number "k" Is Prime.
{
j = 2; // Initialize "j" To 2, The Smallest Prime Number.
while (j * j <= k) // While "j" Squared Is Less Than Or Equal To "k", Check For Factors.
{
if (primes[j] == 1) // If "j" Is Marked As Prime And Divides "k" evenly, Mark "k" As Non-Prime.
{
if (k % j == 0) // ^.
{
primes[k] = 0; // ^.
return; // ^. (Exit).
}
}
j += 1; // Increment "j" To Check The Next Number.
}
primes[k] = 1; // If No Factors Are Found, Mark "k" As Prime.
}
int main() // Main Function.
{
printf("Enter The Upper Bound:\n"); // Prompt The User To Enter An Upper Bound.
scanf("%d", &upper_bound); // Read The Upper Bound From The User.
for (i = 2; i <= upper_bound; i += 1) // Loop Through Numbers From 2 Up To The Upper Bound.
{
check_if_prime(i, primes); // Check If "i" Is A Prime Number.
if (primes[i]) // If "i" Is Marked As Prime, Print That It's A Prime Number.
{
printf("%d Is A Prime\n", i); // ^.
}
}
return 0; // ^. (Exit).
}
