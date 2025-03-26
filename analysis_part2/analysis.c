// L. Kiser Nov. 9, 2023 updated to version 2
// Document Analysis project functions for Part 2

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "analysis.h"
#include "unit_tests.h"

static FILE *validate_read_file_parameters(struct linked_list *p_list, char *file_name)
{
	if (p_list == NULL || file_name == NULL || *file_name == '\0')
	{
	return NULL;
	}
	return fopen(file_name, "r");
}

int process_word(struct linked_list *p_list, char *word)
{
   	int status = 0;
    	if (p_list == NULL || word == NULL || *word == '\0')
	{
        return status;
    	}
    	struct node *current = p_list->p_head;
    	struct node *prev = NULL;
    	while (current != NULL && strcmp(word, current->unique_word) > 0)
	{
        prev = current;
        current = current->p_next;
    	}
    	if (current != NULL && strcmp(word, current->unique_word) == 0)
	{
        current->word_count++;
    	}
	else
	{
        struct node *new_node = create_node(word);
        if (new_node == NULL)
	{
       	return status;
        }
        if (prev == NULL)
	{
        new_node->p_next = p_list->p_head;
        p_list->p_head = new_node;
        if (p_list->p_tail == NULL)
	{
        p_list->p_tail = new_node;
        }
        }
	else
	{
        new_node->p_next = current;
        prev->p_next = new_node;
        if (new_node->p_next == NULL)
	{
        p_list->p_tail = new_node;
        }
        }
    	}
    	return 1;
}

int read_file(struct linked_list *p_list, char *file_name)
{
	FILE *file = validate_read_file_parameters(p_list, file_name);
    	if (file == NULL)
	{
        return 0;
   	}
    	char buffer[100];
    	while (fscanf(file, "%99s", buffer) == 1)
	{
        for (int i = 0; buffer[i] != '\0'; i += 1)
	{
        buffer[i] = tolower(buffer[i]);
        }
	if (!process_word(p_list, buffer))
	{
        fclose(file);
        return 0;
        }
   	}
    	fclose(file);
    	return 1;
}

struct word_entry get_first_entry(struct linked_list *p_list)
{
	struct word_entry entry = {NULL, 0};
   	if (p_list != NULL && p_list->p_head != NULL)
	{
        entry.unique_word = p_list->p_head->unique_word;
        entry.word_count = p_list->p_head->word_count;
        p_list->p_current = p_list->p_head;
   	}
    	return entry;
}

struct word_entry get_next_entry(struct linked_list *p_list)
{
 	struct word_entry entry = {NULL, 0};
    	if (p_list != NULL && p_list->p_current != NULL && p_list->p_current->p_next != NULL)
	{
        p_list->p_current = p_list->p_current->p_next;
        entry.unique_word = p_list->p_current->unique_word;
        entry.word_count = p_list->p_current->word_count;
   	}
   	return entry;
}

struct word_entry get_prev_entry(struct linked_list *p_list)
{
	struct word_entry entry = {NULL, 0};
    	if (p_list != NULL && p_list->p_current != NULL && p_list->p_current != p_list->p_head)
	{
        struct node *temp = p_list->p_head;
        while (temp->p_next != p_list->p_current)
	{
        temp = temp->p_next;
        }
        p_list->p_current = temp;
        entry.unique_word = p_list->p_current->unique_word;
        entry.word_count = p_list->p_current->word_count;
   	}
    	return entry;
}

struct word_entry get_last_entry(struct linked_list *p_list)
{
	struct word_entry entry = {NULL, 0};
    	if (p_list != NULL && p_list->p_tail != NULL)
	{
        entry.unique_word = p_list->p_tail->unique_word;
        entry.word_count = p_list->p_tail->word_count;
        p_list->p_current = p_list->p_tail;
   	}
    	return entry;
}

int write_unique_word_list_to_csv_file(struct linked_list *p_list, char *file_name)
{
	if (p_list == NULL || file_name == NULL || *file_name == '\0')
	{
        return 0;
   	}
    	FILE *file = fopen(file_name, "w");
    	if (file == NULL)
	{
        return 0;
   	}
   	fprintf(file, "word,count\n");
    	struct node *current = p_list->p_head;
    	while (current != NULL)
	{
        fprintf(file, "%s,%d\n", current->unique_word, current->word_count);
        current = current->p_next;
   	}
    	fclose(file);
    	return 1;
}

