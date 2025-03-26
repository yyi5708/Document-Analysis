// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018
// L. Kiser Oct 9, 2023 Updated version (eliminate word_entry struct and added new functions)

#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

struct node
{
	char *unique_word;
	int word_count;
	struct node *p_previous;
	struct node *p_next;
};

struct linked_list
{
	struct node *p_head;
	struct node *p_tail;
	struct node *p_current;
};

struct one_word
{
	char word [100];
        int word_count;
};

extern struct linked_list *get_test_p_list( void ) ;
extern struct node *create_node( char *word ) ;
extern int valid_parameters( struct linked_list *p_list, char *word ) ;
extern int add_node_at_head( struct linked_list *p_list, char *word ) ;
extern int clear_linked_list( struct linked_list *p_list ) ;
extern int add_node_after_current( struct linked_list *p_list, char *word ) ;
extern int find_word( struct linked_list *p_list, char *word ) ;
extern char *get_current_word( struct linked_list *p_list ) ;
extern char *get_previous_word( struct linked_list *p_list ) ;
extern char *get_next_word( struct linked_list *p_list ) ;

#endif

