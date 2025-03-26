// Document Analysis project linked list functions
// L. Kiser Feb. 20, 2018
// L. Kiser Oct 9, 2023 Updated version (eliminate word_entry struct and added new functions)

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list_functions.h"
#include "unit_tests.h"

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

