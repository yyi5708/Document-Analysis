// C pointers final Practicum
// SWEN-250
// Larry Kiser December 8, 2021

#define BOGUS_POINTER (char *)1
#define BAD_PARAMETERS (-999999)

// structs

struct specs
{
	int number_of_letters;	// number of letters to load into the new string at the beginning
	char letter;		// the letter to be written to the new string
	char *p_new_string;	// an optimally size malloc'ed string containing number_of_letters of letter.
};

// cfinal functions

char *insert_second_string(char *p_first, char *p_second);
int create_string(struct specs *p_specs);
int divide_by_two(int *p_integers, int number_of_integers);
int fix_bad_code(char *pstring);
int get_bit(unsigned int value, int bit_position);

