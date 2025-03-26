#Muhammad Yousaf Iqbal

#For the integers in the range 1 to 100 inclusive, print one line per integer:
#If the integer is divisible by 5, print the string "Fizz"
#If the integer is divisible by 7, print the string "Buzz"
#If the integer if divisible by both 5 and 7, print the string "FizzBuzz"
#In all other cases, print the integer itself

def Fizz_Buzz(Integer):

    if (Integer) % (5) == (0) and (Integer) % (7) == (0):
        return ("FizzBuzz")
    if (Integer) % (5) == (0):
        return ("Fizz")
    if (Integer) % (7) == (0):
        return ("Buzz")
    else:
        return (Integer)

def main():

    for (Integers) in range(1, 101):
        Line = Fizz_Buzz(Integers)
        print(Line)

if (__name__) == ("__main__"):

    main()

