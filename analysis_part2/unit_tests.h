// unit_tests.h
// L. Kiser Oct. 28, 2015

// the main unit test
extern int test_analysis( void ) ;
extern int test_linked_list_functions( void ) ;
extern int test_student( void ) ;

// boolean assert function for unit testing
extern int assert( int testresult, char error_message[], ... ) ;
extern void reset_test_counter( void ) ;
