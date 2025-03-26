// analysis.h
// L. Kiser Nov. 20, 2015
// L. Kiser Nov. 9, 2023 updated to version 2

#define MAX_WORD (20)		// maximum length of a legal word_entry

#include "linked_list_functions.h"

// this contains both a pointer to the word and the number of times the word occurs in the document.
struct word_entry
{
    char *unique_word ;         // be sure to malloc exactly enough space to hold the string for the word include the '\0'.
    int word_count ;            // The number of times this word occurs in the input document (by definition at least one).
} ;

// document analysis project functions
int process_word ( struct linked_list *p_list, char *word ) ;
int read_file( struct linked_list *p_list, char *file_name ) ;
struct word_entry get_first_entry( struct linked_list *p_list ) ;
struct word_entry get_next_entry( struct linked_list *p_list ) ;
struct word_entry get_prev_entry( struct linked_list *p_list ) ;
struct word_entry get_last_entry( struct linked_list *p_list ) ;
int write_unique_word_list_to_csv_file( struct linked_list *p_list, char *file_name ) ;
