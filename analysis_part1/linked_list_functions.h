// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018
// L. Kiser Oct 9, 2023 Updated version (eliminate word_entry struct and added new functions)

// This makes sure that we include the header file only once
#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

// document analysis project linked list structs
 
struct node
{
	char *unique_word;
	// be sure to malloc exactly enough space to hold the string for the word include the '\0'.
	int word_count;
	// The number of times this word occurs in the input document (by definition at least one).
	struct node *p_previous;
	// set to NULL if this node is the first in the list.
	struct node *p_next;
	// set to NULL if this node is the last in the list
};

struct linked_list
{
	struct node *p_head;
	// points to the first node in the list. NULL if the list is empty.
	struct node *p_tail;
	// points to the last node in the list. NULL if the list is empty.
	struct node *p_current;
	// points to the most recently added or accessed record. NULL if the list is empty.
};

struct one_word
{
	char word[100];
	int word_count;
};

// linked list function prototypes

extern struct linked_list *get_test_p_list(void);
extern struct node *create_node(char *word);
extern int valid_parameters(struct linked_list *p_list, char *word);
extern int add_node_at_head(struct linked_list *p_list, char *word);
extern int clear_linked_list(struct linked_list *p_list);
extern int add_node_after_current(struct linked_list *p_list, char *word);
extern int find_word(struct linked_list *p_list, char *word);
extern char *get_current_word(struct linked_list *p_list);
extern char *get_previous_word(struct linked_list *p_list);
extern char *get_next_word(struct linked_list *p_list);

#endif	// matches the #ifndef at the beginning that avoids multiple inclusions.

