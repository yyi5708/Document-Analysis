test:	main.o linked_list_functions.o unit_tests.o analysis.o unit_tests_linked_list_functions.o unit_tests_analysis.o unit_tests_student.o
	gcc -o test -g main.o linked_list_functions.o unit_tests.o analysis.o unit_tests_linked_list_functions.o unit_tests_analysis.o unit_tests_student.o
	
main.o:	main.c unit_tests.h 
	gcc -c -g -Wall main.c
	
linked_list_functions.o:	linked_list_functions.c linked_list_functions.h
	gcc -c -g -Wall linked_list_functions.c
	
unit_tests.o:	unit_tests.c unit_tests.h
	gcc -c -g -Wall unit_tests.c
	
unit_tests_analysis.o:	unit_tests_analysis.c unit_tests.h analysis.h
	gcc -c -g -Wall unit_tests_analysis.c
	
unit_tests_student.o:	unit_tests_student.c unit_tests.h analysis.h
	gcc -c -g -Wall unit_tests_student.c
	
unit_tests_linked_list_functions.o:	unit_tests_linked_list_functions.c unit_tests.h linked_list_functions.h
	gcc -c -g -Wall unit_tests_linked_list_functions.c
	
analysis.o:	analysis.c linked_list_functions.h analysis.h
	gcc -c -g -Wall analysis.c

clean:
	rm -rf *.o
	rm -rf test
	
