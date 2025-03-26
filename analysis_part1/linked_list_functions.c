// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018
// L. Kiser Oct 9, 2023 Updated version (eliminate word_entry struct and added new functions)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

// Fully implemented helper function to create a valid linked list
// that does not depend on the student implementation of the library
// functions. Used for testing the get previous, current, and next
// word functions.

struct linked_list *get_test_p_list()
{
	static struct linked_list list;
	static struct node a = {"a", 1, NULL, NULL};
	static struct node b = {"b", 1, NULL, NULL};
	static struct node c = {"c", 1, NULL, NULL};
	list.p_head = &a;
	list.p_current = list.p_head;
	a.p_next = &b;
	b.p_previous = &a;
	b.p_next = &c;
	c.p_previous = &b;
	list.p_tail = &c;
	return &list;
}

// First verifies that p_list is not NULL. If it is NULL return NULL and do nothing else.
// If there is no current record (p_current is NULL) return NULL and do nothing else.
// On success returns a pointer to the word in the current record in the linked list.

char *get_current_word(struct linked_list *p_list) 
{
	if (p_list == NULL)
	{
	return NULL;
	}
	if (p_list->p_current == NULL)
	{
	return NULL;
	}
	struct one_word *word = (struct one_word *)(p_list->p_current->unique_word);
	return word->word;
}

// First verifies that p_list is not NULL. If it is NULL return NULL and do nothing else.
// If there is no current record (p_current is NULL) return NULL and do nothing else.
// If p_current is not NULL test to see if there is a previous record.
// NOTE -- use the get_current_word function to verify p_list and p_current.
// Next verify the p_previous is not NULL.
// If p_previous is NULL return NULL and keep p_current at the same position.
// If there is a previous entry change p_current to point to the previous record and
// return a pointer to the word in this new current record.

char *get_previous_word(struct linked_list *p_list)
{
	if (p_list == NULL)
	{
	return NULL;
	}
	char *current_word = get_current_word(p_list);
	if (current_word == NULL)
	{
	return NULL;
	}
	if (p_list->p_current->p_previous != NULL)
	{
	p_list->p_current = p_list->p_current->p_previous;
	return get_current_word(p_list);
	}
	return NULL;
}

// First verifies that p_list is not NULL. If it is NULL return NULL and do nothing else.
// If there is no current record (p_current is NULL) return NULL and do nothing else.
// If p_current is not NULL test to see if there is a next record.
// If there is no next record return NULL and keep p_current at the same position.
// If there is a next record change p_current to point to the next record and
// return a pointer to the word in this new current record.

char *get_next_word(struct linked_list *p_list)
{
	if (p_list == NULL)
	{
	return NULL;
	}
	char *current_word = get_current_word(p_list);
	if (current_word == NULL)
	{
	return NULL;
	}
	if (p_list->p_current->p_next != NULL)
	{
	p_list->p_current = p_list->p_current->p_next;
	return get_current_word(p_list);
	}
	return NULL;
}

// Implement this function first to create an initialized linked list node.
// It must allocate space for the passed string in the one_word structure.
// It must copy the passed string into that structure and sets its word count to 1.
// Assume that the passed word points is not NULL and is not an empty string.
// The calling function is responsible for passing a valid string.
// This function returns a pointer to the allocated node.

struct node *create_node(char *word)
{	
	if (word == NULL)
	{
	return NULL;
	}
	struct one_word *unique_word = malloc(sizeof(struct one_word));
        if (unique_word == NULL)
	{
	return NULL;
	}
	strcpy(unique_word->word, word);
	unique_word->word_count = 1;
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL)
	{
	free(unique_word);
	return NULL;
	}
	new_node->unique_word = (void*) unique_word;
	new_node->word_count = 1;
	new_node->p_next = NULL;
	return new_node;
}

// Implement this function right after you get create_node working.
// This is a helper function that your are required to use in the following
// functions that need to verify that p_list is not NULL and word is not NULL
// and word is not an empty string.
// Returns 1 if all three tests pass. Returns 0 if any test fails.

int valid_parameters(struct linked_list *p_list, char *word)
{
	if (p_list == NULL)
	{
	return 0;
	}
	if (word == NULL)
	{
	return 0;
	}
	if (strlen(word) == 0)
	{
	return 0;
	}
	return 1;
}

// Inserts a node at the beginning of the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// Use the valid parameters function to verify parameters.
// Return 0 if not valid parameters.
//
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the passed p_head and p_current members of p_list.
// p_head and p_current will always point to the newly added node.
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.

int add_node_at_head(struct linked_list *p_list, char *word)
{
	if (!valid_parameters(p_list, word))
	{
	return 0;
	}
	struct node *new_node = create_node(word);
	if (new_node == NULL)
	{
	return 0;
	}
	if (p_list->p_head == NULL)
	{
	p_list->p_head = new_node;
	p_list->p_tail = new_node;
	}
	else
	{
	new_node->p_next = p_list->p_head;
	p_list->p_head->p_previous = new_node;
	p_list->p_head = new_node;
	}
	p_list->p_current = new_node;
	return 1;
}

// If p_list is NULL return 0.
// For the passed linked_list pointer free all of the nodes in the list.
// Be careful to free the space for the string before freeing the node itself.
// Also be careful to save a copy of the pointer to the next item in the list before
// freeing the node.
// Lastly, return the number of nodes freed (which could be zero if p_list indicates an empty list).

int clear_linked_list(struct linked_list *p_list)
{
	if (p_list == NULL)
	{
	return 0;
	}
	int nodes_freed = 0;
	struct node *current_node = p_list->p_head;
	while (current_node != NULL)
	{
	struct node *next_node = current_node->p_next;
	struct one_word *word = (struct one_word *)(current_node->unique_word);
	free(word);
	free(current_node);
	nodes_freed += 1;
	current_node = next_node;
	}
	p_list->p_head = NULL;
	p_list->p_tail = NULL;
	p_list->p_current = NULL;
	return nodes_freed;
}

// Inserts a node after the current pointer in the linked list.
// Updates the passed set of pointers as needed based upon the addition that was done.
//
// It checks that p_list is not NULL. Checks that word is not NULL and is not an empty string. 
// Call the valid_parameters function to verify the input parameters. Return 0 on bad parameters.
// Also on failure no change is made to the pointers in p_list.
//
// On success it returns a 1 and updates at least the p_current member of p_list. p_current points to the newly added node.
// p_head is updated only if p_current is NULL (an empty list).
// p_tail is updated only if the new node is at the end of the list.
//
// When adding the first node to an empty list p_tail will also point to this same new node since it is the only node.
//
// Hint: use the create_node function to actually create the node.
// Hint: be sure to maintain both the p_previous and p_next pointers in each node.
// Hint: if this function is called with a p_current that is NULL (meaning the list is empty)
//       use the add_node_at_head function to create the new node.

int add_node_after_current(struct linked_list *p_list, char *word)
{
	if (!valid_parameters(p_list, word))
   	{
        return 0;
    	}
    	struct node *new_node = create_node(word);
    	if (new_node == NULL)
    	{
        return 0;
    	}
	if (p_list->p_current == NULL)
    	{
        return add_node_at_head(p_list, word);
   	}
    	else
    	{
        new_node->p_next = p_list->p_current->p_next;
        if (p_list->p_current->p_next != NULL)
	{
        p_list->p_current->p_next->p_previous = new_node;
        }
        p_list->p_current->p_next = new_node;
        new_node->p_previous = p_list->p_current;
        if (p_list->p_current == p_list->p_tail)
	{
        p_list->p_tail = new_node;
        }
        p_list->p_current = new_node;
   	}
    	return 1;
}

// Searches the linked list for the passed word.
// Always starts searching at the first entry.
// NOTE -- this function REQUIRES that the linked list has been maintained in English language alphabetical order.
// Definition of match: every letter must match exactly including by case.
// e.g. "A" does NOT match "a". "a " does NOT match "a"
//
// If found it sets the current pointer to the matching node.
// If not found it returns a failure and sets the current pointer to the node just before the
// insertion point (by alphabetic order). Note the special case for a new word that goes at the
// beginning of the list. See the examples below.
//
// Hint: use strcmp to determine sorting order.
//
// If it is found the current pointer is set to the node containing the matching word.
// If it is found this function returns a 1 to indicate success.
//
// If it is not found the current pointer is set to the node just before the insertion point.
// If it is not found the function returns a 0 to indicate failure.
// e.g. the list contains the words "apple", "buy", "cat".
//      Searching for "baby" would set current to the node containing "apple".
//      Searching for "acid" would set current to NULL to indicate that "acid" belongs at the head.
//      searching for "zebra" would set current to the node containing "cat".
//
// Tests on p_list and word: p_list, p_list->head, and word must all not be NULL.
// In addition, word must not be an empty string.
// We must have a valid list with at least one node and we must a valid word to match.
// If any of these conditions are violated this function returns a -1 to indicate invalid input.
//
// Hint -- the valid_parameters and get current, next, and previous word functions may be useful.
//
// return value summary: -1 if input parameters are bad, 0 if not found, 1 if found.

int find_word(struct linked_list *p_list, char *word)
{
	if (p_list == NULL || p_list->p_head == NULL || word == NULL || strlen(word) == 0)
	{
	return -1;
	}
	struct node* node = p_list->p_head;
	while (node != NULL)
	{
	int result = strcmp(word, node->unique_word);
	if (result < 0)
	{
	p_list->p_current = node->p_previous;
	return 0;
	}
	if (result == 0)
	{
	p_list->p_current = node;
	return 1;
	}
	if (result > 0)
	{
	node = node->p_next;
	}
	}
	p_list->p_current = p_list->p_tail;
	return 0;
}

