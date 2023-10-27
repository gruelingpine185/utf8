#ifndef UTF8_STRING_H
#define UTF8_STRING_H


#include <stddef.h>
#include <stdint.h>


typedef uint32_t utf8_codepoint;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
size_t utf8_strlen(const char* _str);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // UTF8_STRING_H
