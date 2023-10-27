#ifndef UTF8_STRING_H
#define UTF8_STRING_H


#include <stddef.h>
#include <stdint.h>


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

/**
 * Determines the length of a given string in codepoints up to a given maximum,
 * excluding the terminating null byte.
 * 
 * If there exists a null terminator in string before the maximim length is met,
 * or an unexpected codepoint is encountered, this function will return the
 * length of the given string up to that point.
 * 
 * Returns the length of the string.
*/
size_t utf8_strnlen(const char* _str, size_t _max);

/**
 * Compares sequential byte values of two given strings.
 *
 * Returns 0 if both strings are identical. If the numeric value at any offset
 * of str1 is less than that of str2 at the same offset, then -1 is returned,
 * otherwise 1 is returned.
*/
int utf8_strcmp(const char* _str1, const char* _str2);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTF8_STRING_H
