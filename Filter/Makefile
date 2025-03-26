test_filter: test_filter.o filter.o
	gcc -g -o test_filter test_filter.o filter.o

test_filter.o: test_filter.c filter.h
	gcc -g -c test_filter.c

filter.o: filter.c filter.h
	gcc -g -Wall -c filter.c

clean:
	rm -f test_filter test_filter.exe
	rm -f *.o *.bak *~*
