HEADERS = cpracticum2.h unit_tests.h

default: test

test:	main.o cpracticum2.o unit_tests.o
	gcc -g -o test main.o cpracticum2.o unit_tests.o
	
cpracticum2.o: cpracticum2.c $(HEADERS)
	gcc -Wall -g -c cpracticum2.c

main.o: main.c $(HEADERS)
	gcc -Wall -g -c main.c
	
unit_tests.o: unit_tests.c $(HEADERS)
	gcc -Wall -g -c unit_tests.c

clean:
	-rm -f cpracticum2.o
	-rm -f main.o
	-rm -f unit_tests.o
	-rm -f test
	
