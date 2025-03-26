HEADERS = cpracticum1.h unit_tests.h

default: test

test:	cpracticum1.o unit_tests.o
	gcc -o test -g cpracticum1.o unit_tests.o
	
cpracticum1.o: cpracticum1.c $(HEADERS)
	gcc -c -g -Wall cpracticum1.c

unit_tests.o: unit_tests.c $(HEADERS)
	gcc -c -g -Wall unit_tests.c

clean:
	-rm -f cpracticum1.o
	-rm -f unit_tests.o
	-rm -f test
	
