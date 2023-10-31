#include <assert.h>
#include <stdlib.h>

#include "string.h"


/**
 * A lookup table used to determine the quantity of bytes in succession of each
 * other based on an initial byte. This map is offset by -1 to respect the fact
 * that the initial byte is not being accounted for.
*/
const int codepoint_len_lookup[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3,
    -1, -1, -1, -1, -1, -1, -1, -1
};


/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from -1 to 3 (inclusive). -1 indicates an invalid codepoint. 
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


const char* utf8_advance_to_start(const char* _str) {
    if(!_str) return NULL;

    int bytes = 0;
    do {
        bytes = utf8_get_expected_bytes(*_str);
        if(bytes) return _str;
    } while(*_str++);

    return NULL;
}

int utf8_get_expected_bytes(uint32_t _cp) {
    return codepoint_len_lookup[_cp];
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
