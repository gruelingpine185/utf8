#include <assert.h>
#include <stdlib.h>

#include "string.h"


/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from 0 to 3 if successful, otherwise returns -1.
*/
int utf8_get_expected_bytes(uint32_t _cp);

/**
 * Collects a single codepoint pointed to by the given string.
 * 
 * This codepoint is expected to have 0 to 3 bytes following the initial byte.
 * If any other value is passed to _bytes, NULL is returned.
 * 
 * If the codepoint expects more bytes than is in the given string, NULL is
 * returned.
 * 
 * Returns an allocated NULL terminated string holding the codepoint pointed to
 * by _str.
*/
char* utf8_codepoint_to_str(const char* _str, int _bytes);


int utf8_get_expected_bytes(uint32_t _cp) {
    if((_cp & 0x80) == 0)    return 0;   // 0b0xxx xxxx
    if((_cp & 0xe0) == 0xc0) return 1;   // 0b110x xxxx
    if((_cp & 0xf0) == 0xe0) return 2;   // 0b1110 xxxx
    if((_cp & 0xf8) == 0xf0) return 3;   // 0b1111 0xxx
    
    return -1;
}

char* utf8_codepoint_to_str(const char* _str, int _bytes) {
    assert(_str != NULL);
    assert((_bytes < 3) || (_bytes > 0));
    if(!_str || ((_bytes < 0) || (_bytes > 3))) return NULL;

    // +1 to get bytes including the current, and +1 for Null terminator
    char* cp = (char*) malloc(sizeof(*cp) * (_bytes + 2));
    if(!cp) return NULL;

    for(int i = 0; i < _bytes + 1; i++) {
        cp[i] = *_str;
        if(!*_str++) {
            free(cp);
            return NULL;
        }
    }

    cp[_bytes + 2] = '\0';
    return cp;
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
    if(!_str1 || !_str2) return -2;

    do {
        if(*_str1 != *_str2) break;

        _str1++;
        _str2++;
    } while(*_str1 && *_str2);

    if(*_str1 < *_str2) return -1;
    if(*_str1 > *_str2) return 1;

    return 0;
}

int utf8_strncmp(const char* _str1, const char* _str2, size_t _max) {
    assert(_str1 != NULL);
    assert(_str2 != NULL);
    if(!_max || !_str1 || !_str2) return -2;

    size_t i = 0;
    do {
        if(*_str1 != *_str2) break;

        _str1++;
        _str2++;
        i++;
    } while(i < _max);

    if(*_str1 < *_str2) return -1;
    if(*_str1 > *_str2) return 1;

    return 0;
}

char* utf8_codepoint_at(const char* _str, size_t _offset) {
    assert(_str != NULL);
    if(!_str) return NULL;

    size_t i = 0;
    int bytes = 0;
    do {
        bytes = utf8_get_expected_bytes(*_str);
        if(bytes < 0) return NULL;
        if(i == _offset) return utf8_codepoint_to_str(_str, bytes);

        i++;
    } while(*(_str += bytes + 1));

    return NULL;
}
