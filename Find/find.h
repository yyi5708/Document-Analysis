#ifndef FIND_H

#define FIND_H

int find_ch_index(char string[], char ch);
char *find_ch_ptr(char *string, char ch);
int find_any_index(char string[], char stop[]);
char *find_any_ptr(char *string, char* stop);
char *find_substr(char *string, char* substr);

#endif
