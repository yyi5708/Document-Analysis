EADERS = c_final.h unit_tests.h

default: test

test:	main.o c_final.o unit_tests.o
	gcc -g -o test main.o c_final.o unit_tests.o
	
c_final.o: c_final.c $(HEADERS)
	gcc -Wall -g -c c_final.c

main.o: main.c $(HEADERS)
	gcc -Wall -g -c main.c
	
unit_tests.o: unit_tests.c $(HEADERS)
	gcc -Wall -g -c unit_tests.c

clean:
	-rm -f c_final.o
	-rm -f main.o
	-rm -f unit_tests.o
	-rm -f test
	
