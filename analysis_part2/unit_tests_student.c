// unit_tests student additions
// Larry L. Kiser Oct. 22, 2015

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "analysis.h"
#include "unit_tests_analysis.h"
#include "unit_tests.h"

int test_student()
{
	int passcount = 0;
	int failcount = 0;
    	struct linked_list list1;
	memset(&list1, 0, sizeof(list1));
    	printf("\n========= student generated tests on MLK excerpt ===============================\n");
    	int result = read_file(&list1, "MLK_dream_excerpt.txt");
    	assert(result == 113, "1 read_file processing MLK_dream_excerpt. Expect word count of 113 returned but got %d.", result) ? passcount ++ : failcount ++ ;
    	struct word_entry current_entry = get_first_entry(&list1);
    	int day_count = 0;
	while (current_entry.unique_word != NULL)
	{
        if (strcmp(current_entry.unique_word, "day") == 0)
	{
        day_count = current_entry.word_count;
        break;
        }
        current_entry = get_next_entry(&list1);
    	}
    	assert(day_count == 3, "Word 'day' should occur 3 times, but got %d", day_count);
    	current_entry = get_first_entry(&list1);
    	char *word_after_have = NULL;
    	while (current_entry.unique_word != NULL)
	{
        if (strcmp(current_entry.unique_word, "have") == 0)
	{
        current_entry = get_next_entry(&list1);
       	word_after_have = current_entry.unique_word;
        break;
        }
        current_entry = get_next_entry(&list1);
   	}
	assert(strcmp(word_after_have, "heat") == 0, "Word after 'have' should be 'heat', but got %s", word_after_have);
	struct word_entry last_entry = get_last_entry(&list1);
    	assert(strcmp(last_entry.unique_word, "with") == 0, "Last word in the list should be 'with', but got %s", last_entry.unique_word);
	current_entry = get_first_entry(&list1);
    	while (current_entry.unique_word != NULL)
	{
        if (get_next_entry(&list1).unique_word != NULL && get_next_entry(&list1).unique_word != NULL)
	{
        current_entry = get_next_entry(&list1);
        }
	else
	{
        break;
        }
   	}
	assert(strcmp(current_entry.unique_word, "will") == 0, "Next to the last word should be 'will', but got %s", current_entry.unique_word);
    	result = clear_linked_list(&list1);
    	assert(result == 62, "6 clear linked list expected to remove 62 entries but got %d.", result) ? passcount ++ : failcount ++ ;
    	printf("\nSummary of analysis unit tests:\n%d tests passed\n%d tests failed\n\n", passcount, failcount);
    	return failcount;
}

