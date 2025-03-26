// csv.h
// L. Kiser Oct. 21, 2015

/*
 * Boolean here - just so we don't have to import a text file.
 */

typedef enum { false, true } bool ;

#define MAX_FIELDS	(15)	/* maximum fields on a CSV input line */
#define MAX_CHARS	(20)	/* maximum characters in any one field */

/*
 * Just an array of characters representing a single filed.
*/

typedef char f_string[MAX_CHARS+1] ;	/* string for each field */

/*
 * A parsed CSV line, with the number of fields and upto MAX_FIELDS themselves.
*/

typedef struct {
	int nfields ;				/* 0 => end of file */
	f_string field[MAX_FIELDS] ;		/* array of strings for fields */
} csv_line ;

// csv functions
bool is_end_of_field(int ch) ;
int min(int x, int y) ;
int get_field(f_string field) ;
csv_line get_line() ;
void print_csv(csv_line header, csv_line data) ;
