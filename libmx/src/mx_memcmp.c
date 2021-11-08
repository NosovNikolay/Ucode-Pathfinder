#include "libmx.h"


int mx_memcmp(const void* s1, const void* s2, size_t n) {
    if (n == 0) {
        return 0;
    }
    const unsigned char* _s1 = (const unsigned char*)s1;
    const unsigned char* _s2 = (const unsigned char*)s2;
    size_t i = 0;
    while (i != n && _s1[i] == _s2[i]) {
        _s1++;
        _s2++;
    }
    return *_s1 - *_s2;
}

