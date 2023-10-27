#ifndef UTF8_STRING_H
#define UTF8_STRING_H


#include <stddef.h>
#include <stdint.h>


typedef uint32_t utf8_codepoint;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
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
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTF8_STRING_H
