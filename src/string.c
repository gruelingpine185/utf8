/**
 * Determines the amount of expected contiguous bytes not including the given
 * codepoint.
 *
 * Returns a value from 0 to 3 if successful, otherwise returns -1.
 *
*/
int utf8_get_expected_bytes(int _cp);


int utf8_get_expected_bytes(int _cp) {
    if((_cp & 0x80) == 0)    return 0;   // 0b0xxx xxxx
    if((_cp & 0xe0) == 0xc0) return 1;   // 0b110x xxxx
    if((_cp & 0xf0) == 0xe0) return 2;   // 0b1110 xxxx
    if((_cp & 0xf8) == 0xf0) return 3;   // 0b1111 0xxx
    
    return -1;
}
