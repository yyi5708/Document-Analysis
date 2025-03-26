#include <stdlib.h>

#include <stdbool.h>

#include "find.h"

#define NOT_FOUND (-1)

int find_ch_index(char string[], char ch) {
    int index = 0;
    while (string[index] != '\0') {
        if (string[index] == ch) {
            return index;
        }
        index += 1;
    }
    return NOT_FOUND;
}

char *find_ch_ptr(char *string, char ch) {
    while (*string != '\0') {
        if (*string == ch) {
            return string;
        }
        string += 1;
    }
    return NULL;
}

int find_any_index(char string[], char stop[]) {
    int index = 0;
    while (string[index] != '\0') {
        int stopIndex = 0;
        while (stop[stopIndex] != '\0') {
            if (string[index] == stop[stopIndex]) {
                return index;
            }
            stopIndex += 1;
        }
        index += 1;
    }
    return NOT_FOUND;
}

char *find_any_ptr(char *string, char* stop) {
    while (*string != '\0') {
        char *stopPtr = stop;
        while (*stopPtr != '\0') {
            if (*string == *stopPtr) {
                return string;
            }
            stopPtr += 1;
        }
        string += 1;
    }
    return NULL;
}

char *find_substr(char *string, char *substr) {
    if (*substr == '\0') {
        return string;
    }
    while (*string != '\0') {
        char *stringPtr = string;
        char *substrPtr = substr;
        while (*substrPtr != '\0' && *stringPtr == *substrPtr) {
            stringPtr += 1;
            substrPtr += 1;
        }
        if (*substrPtr == '\0') {
            return string;
        }
        string += 1;
    }
    return NULL;
}
