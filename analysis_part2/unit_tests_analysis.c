// unit_tests.c
// Larry L. Kiser Oct. 22, 2015
// Updated to version 2.0 Nov. 9, 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "analysis.h"
#include "unit_tests_analysis.h"
#include "unit_tests.h"

//////////////////////////////////////////////////////////////////////////
// Begin unit tests //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// do the unit tests
// returns the number of failed tests.
int test_analysis()
{
	int passcount = 0 ;
	int failcount = 0 ;
	struct linked_list list1 ;		// list list pointers for one list
	
	// Initialize local stack data
	memset( &list1, 0, sizeof( list1 ) ) ;		// set all pointers to NULL (zero)
	
	printf( "\n========= tests for process_word ===============================================\n" ) ;
	int result = process_word( NULL, "one" ) ;
	assert( result == 0,
		"1 process_word must return 0 if p_list is a NULL pointer but got %d", result )
		? passcount++ : failcount++ ;
	
	result = process_word( &list1, NULL ) ;
	assert( result == 0,
		"2 process_word must return 0 if word is a NULL pointer but got %d", result )
		? passcount++ : failcount++ ;
	
	result = process_word( &list1, "" ) ;
	assert( result == 0,
		"3 process_word must return 0 if word is an empty string but got %d", result )
		? passcount++ : failcount++ ;
	
	result = process_word( &list1, "first" ) ;
	assert( result == 1,
		"4 process_word must return 1 because we added it to the empty list but got %d", result )
		? passcount++ : failcount++ ;
	// list now has "first"
	assert( list1.p_head != NULL && list1.p_head->unique_word != NULL,
		"5 The head of the list must not be NULL and the unique word must NOT be NULL but at least one is NULL" )
		? passcount++ : failcount++ ;
	
	// stop here if we cannot add anything to the list.
	if ( failcount > 0 )
		return failcount ;
	
	assert( strcmp( list1.p_head->unique_word, "first" ) == 0,
		"6 Expect the head of the list to  1 because we added it to the empty list but got %d", result )
		? passcount++ : failcount++ ;
		
	assert( list1.p_head == list1.p_tail && list1.p_head == list1.p_current,
		"7 The head, current, and tail pointers must all be the same with only one word in the list" )
		? passcount++ : failcount++ ;
		
	result = process_word( &list1, "zed" ) ;
	assert( result == 1,
		"8 process_word must return 1 because we added \"zed\" to the list but got %d", result )
		? passcount++ : failcount++ ;
	
	assert( list1.p_tail != NULL && list1.p_tail->unique_word != NULL,
		"9 The tail of the list must not be NULL and the->unique_word must not be NULL but at least one is NULL" )
		? passcount++ : failcount++ ;
	
	assert( strcmp( list1.p_tail->unique_word, "zed" ) == 0,
		"10 The tail of the list must now be \"zed\" but it is %s", list1.p_tail->unique_word )
		? passcount++ : failcount++ ;
	// list now has "first" and "zed"
	result = process_word( &list1, "middle" ) ;
	assert( strcmp( list1.p_current->unique_word, "middle" ) == 0,
		"11 The current pointer of the list must point to \"middle\" but it points to %s", list1.p_current->unique_word )
		? passcount++ : failcount++ ;
	// list now has "first", "middle, and "zed"
	result = process_word( &list1, "middle" ) ;
	assert( strcmp( list1.p_current->unique_word, "middle" ) == 0,
		"12 Added a second occurrence of middle. The current pointer of the list must still point to \"middle\" but it points to %s", list1.p_current->unique_word )
		? passcount++ : failcount++ ;
	
	assert( list1.p_current->word_count == 2,
		"13 Added a second occurrence of middle. The word_count must be 2 but it is %d", list1.p_current->word_count )
		? passcount++ : failcount++ ;
	// "middle" now has count of 2
	printf( "\n========= tests for get_first_entry =============================================\n" ) ;
	struct word_entry entry = get_first_entry( NULL ) ;
	assert( entry.word_count == 0,
		"14 get first entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	struct linked_list list2 = { NULL, NULL, NULL } ;
	entry = get_first_entry( &list2 ) ;
	assert( entry.word_count == 0,
		"15 get first entry must return 0 in word_count because list2 is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_first_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "first" ) == 0,
		"16 get first entry which should be \"first\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	printf( "\n========= tests for get_next_entry ==============================================\n" ) ;
	entry = get_next_entry( NULL ) ;
	assert( entry.word_count == 0,
		"17 get next entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list2 ) ;
	assert( entry.word_count == 0,
		"18 get next entry must return 0 in word_count because the list2 list is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;

	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 2 && strcmp( entry.unique_word, "middle" ) == 0,
		"19 get next entry which should be \"middle\" with a count of 2 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "zed" ) == 0,
		"20 get next entry which should be \"zed\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 0,
		"21 get next entry which fail due to the end of the list with a count of 0 but got %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	printf( "\n========= tests for get_last_entry =============================================\n" ) ;
	entry = get_last_entry( NULL ) ;
	assert( entry.word_count == 0,
		"22 get last entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_last_entry( &list2 ) ;		// Note that list2 is still an empty list.
	assert( entry.word_count == 0,
		"23 get last entry must return 0 in word_count because list2 is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_last_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "zed" ) == 0,
		"24 get last entry which should be \"zed\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	printf( "\n========= tests for get_prev_entry ==============================================\n" ) ;
	entry = get_prev_entry( NULL ) ;
	assert( entry.word_count == 0,
		"25 get prev entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list2 ) ;
	assert( entry.word_count == 0,
		"26 get prev entry must return 0 in word_count because the list2 list is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;

	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 2 && strcmp( entry.unique_word, "middle" ) == 0,
		"27 get prev entry which should be \"middle\" with a count of 2 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "first" ) == 0,
		"28 get prev entry which should be \"first\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 0,
		"29 get prev entry which fail due to getting to the beginning of the list with a count of 0 but got %d.", entry.word_count )
		? passcount++ : failcount++ ;
		
	result = clear_linked_list( &list1 ) ;
	assert( result == 3,
		"30 Clear out 3 records in the list but got %d.", result )
		? passcount++ : failcount++ ;
		
	
	printf( "\n========= tests for read_file ==================================================\n" ) ;
	result = read_file( &list1, NULL ) ;
	assert( result == 0,
		"31 read_file file name string must not be a NULL pointer" )
		? passcount++ : failcount++ ;
	
	result = read_file( &list1, "" ) ;
	assert( result == 0,
		"32 read_file file name string must not be empty. " )
		? passcount++ : failcount++ ;
	
	result = read_file( NULL, "empty.txt" ) ;
	assert( result == 0,
		"33 read_file linked list pointer must not be a NULL pointer" )
		? passcount++ : failcount++ ;
	
	result = read_file( &list1, "bogus_file_that_does_not_exist.txt" ) ;
	assert( result == 0,
		"34 read_file must fail if the requested file does not exist." )
		? passcount++ : failcount++ ;
	
	result = read_file( &list1, "one_word.txt" ) ;
	assert( result == 1,
		"35 read_file processing one_word.txt. Expect word count of 1 returned but got %d.", result )
		? passcount++ : failcount++ ;
	
	entry = get_first_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "first" ) == 0,
		"36 read_file did not read one_word.txt correctly. The first word which should be \"first\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	result = read_file( &list1, "five_words.txt" ) ;
	assert( result == 5,
		"37 read_file processing five_words.txt. Expect word count of 5 returned but got %d.", result )
		? passcount++ : failcount++ ;
	
	printf( "\n========= now verify that the five word file was read in correctly =============\n" ) ;
	entry = get_first_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "first" ) == 0,
		"38 read_file did not read one_word.txt correctly. The first word which should be \"first\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( NULL ) ;
	assert( entry.word_count == 0,
		"39 get next entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list2 ) ;
	assert( entry.word_count == 0,
		"40 get next entry must return 0 in word_count because the list2 list is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;

	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "five" ) == 0,
		"41 get next entry which should be \"five\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "four" ) == 0,
		"42 get next entry which should be \"four\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "one") == 0,
		"43 get next entry which should be \"one\"with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "three" ) == 0,
		"44 get next entry which should be \"three\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "two" ) == 0,
		"45 get next entry which should be \"two\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_next_entry( &list1 ) ;
	assert( entry.word_count == 0,
		"46 get next entry which fail due to the end of the list with a count of 0 but got %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	printf( "\n========= now check that the reverse order is correct =========================\n" ) ;
	entry = get_last_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "two" ) == 0,
		"47 get last entry which should be \"two\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	printf( "\n========= tests for get_prev_entry ==============================================\n" ) ;
	entry = get_prev_entry( NULL ) ;
	assert( entry.word_count == 0,
		"48 get prev entry must return 0 in word_count because the p_list pointer is NULL but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list2 ) ;
	assert( entry.word_count == 0,
		"49 get prev entry must return 0 in word_count because the list2 list is an empty list but got word_count of %d.", entry.word_count )
		? passcount++ : failcount++ ;

	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "three" ) == 0,
		"50 get prev entry which should be \"three\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "one" ) == 0,
		"51 get prev entry which should be \"one\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "four") == 0,
		"52 get prev entry which should be \"four\"with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "five" ) == 0,
		"53 get prev entry which should be \"five\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 1 && strcmp( entry.unique_word, "first" ) == 0,
		"54 get prev entry which should be \"first\" with a count of 1 but got %s %d.", entry.unique_word, entry.word_count )
		? passcount++ : failcount++ ;
	
	entry = get_prev_entry( &list1 ) ;
	assert( entry.word_count == 0,
		"55 get prev entry which fail due to getting to the beginning of the list with a count of 0 but got %d.", entry.word_count )
		? passcount++ : failcount++ ;
	
	result = clear_linked_list( &list1 ) ;
	assert( result == 6,
		"56 clear linked list expected to remove 6 entries but got %d.", result )
		? passcount++ : failcount++ ;

	printf( "\n========= tests for the MLK dream excerpt ======================================\n" ) ;
	result = read_file( &list1, "MLK_dream_excerpt.txt" ) ;
	assert( result == 113,
		"57 read_file processing MLK_dream_excerpt. Expect word count of 113 returned but got %d.", result )
		? passcount++ : failcount++ ;
	
	assert( strcmp( list1.p_head->unique_word, "a" ) == 0 && list1.p_head->word_count == 6,
		"58 First word must be \"a\" with a count of 6 but got first word of %s count %d", list1.p_head->unique_word,
		list1.p_head->word_count )
		? passcount++ : failcount++ ;
	
	result = write_unique_word_list_to_csv_file( &list1, "MLK.csv" ) ;
	assert( result == 1,
		"59 Failure to create the MLK.csv output file" )
		? passcount++ : failcount++ ;

	result = clear_linked_list( &list1 ) ;
	assert( result == 62,
		"60 clear linked list expected to remove 62 entries but got %d.", result )
		? passcount++ : failcount++ ;

	printf( "\nSummary of analysis unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount ) ;
	
	return failcount ;
}
