#include <assert.h>

#include "string.h"


/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from 0 to 3 if successful, otherwise returns -1.
*/
int utf8_get_expected_bytes(int _cp);


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

size_t utf8_strnlen(const char* _str, size_t _max) {
    assert(_str != NULL);
    assert(_max != 0);
    if(!_str || !_max) return 0;

    size_t len = 0;
    int bytes = 0;
    do {
        bytes = utf8_get_expected_bytes(*_str);
        if(bytes < 0) return len;
        if(!*(_str += bytes + 1)) return len;

        len++;
    } while(len < _max);

    return len;
}

int utf8_strcmp(const char* _str1, const char* _str2) {
    assert(_str1 != NULL);
    assert(_str2 != NULL);
    do {
        if(*_str1 != *_str2) break;

        _str1++;
        _str2++;
    } while(*_str1 && *_str2);

    if(*_str1 < *_str2) return -1;
    if(*_str1 > *_str2) return 1;

    return 0;
}
