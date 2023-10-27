#include <assert.h>

#include "string.h"


/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from 0 to 3 if successful, otherwise returns -1.
 *
*/
int utf8_get_expected_bytes(int _cp);

/**
 * Determines the length of a given string in codepoints, excluding the
 * terminating null byte.
 *
 * If an unexpected codepoint is encountered, this function will return the
 * length of the given string up to that point.
 * 
 * Returns the length of the string.
*/
size_t utf8_strlen(const char* _str);


int utf8_get_expected_bytes(int _cp) {
    if((_cp & 0x80) == 0)    return 0;   // 0b0xxx xxxx
    if((_cp & 0xe0) == 0xc0) return 1;   // 0b110x xxxx
    if((_cp & 0xf0) == 0xe0) return 2;   // 0b1110 xxxx
    if((_cp & 0xf8) == 0xf0) return 3;   // 0b1111 0xxx
    
    return -1;
}

size_t utf8_strlen(const char* _str) {
    assert(_str != NULL);
    if(!_str) return 0;

    size_t len = 0;
    int bytes = 0;
    do {
        bytes = utf8_get_expected_bytes(*_str);
        if(bytes < 0) return len;

        len++;
    } while(*(_str += bytes + 1));

    return len;
}
