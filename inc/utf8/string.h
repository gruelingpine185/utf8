#ifndef UTF8_STRING_H
#define UTF8_STRING_H


#include <stddef.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from -1 to 3 (inclusive). -1 indicates an invalid codepoint. 
*/
int utf8_get_expected_bytes(uint32_t _cp);

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
 * If there exists a null terminator in string before the maximum length is met,
 * or an unexpected codepoint is encountered, this function will return the
 * length of the given string up to that point.
 * 
 * Returns the length of the string.
*/
size_t utf8_strnlen(const char* _str, size_t _max);

/**
 * Compares sequential byte values of two given strings.
 * 
 * If either string is NULL, this function returns -2.
 * 
 * Returns 0 if both strings are identical. If the numeric value at any offset
 * of str1 is less than that of str2 at the same offset, then -1 is returned,
 * otherwise 1 is returned.
*/
int utf8_strcmp(const char* _str1, const char* _str2);

/**
 * Compares sequential byte values of two given strings up to a given maximum.
 *
 * If the maximum value is set to 0, or either string is NULL, this function
 * returns -2.
 *
 * Returns 0 if both strings are identical. If the numeric value at any offset
 * of str1 is less than that of str2 at the same offset, then -1 is returned,
 * otherwise 1 is returned.
*/
int utf8_strncmp(const char* _str1, const char* _str2, size_t _max);

/**
 * Collects the codepoint at a given offset (in codepoints) within a given
 * string.
 * 
 * If the offset given is less the amount of codepoints within the string, NULL
 * is returned.
 * 
 * Returns a NULL terminated allocated string consisting solely of the
 * codepoint.
*/
char* utf8_codepoint_at(const char* _str, size_t _offset);

/**
 * If the given string points to an invalid starting point, it traverses the
 * string until the start of the next codepoint. This function does not check
 * the validity of codepoint it lands on.
 * 
 * Returns a pointer to the start of the next codepoint. If the string ends
 * before the next codepoint is found, or the string itself is NULL, NULL is
 * returned.
*/
const char* utf8_advance_to_start(const char* _str);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTF8_STRING_H
