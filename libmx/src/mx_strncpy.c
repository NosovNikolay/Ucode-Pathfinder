#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    char *begin = dst;
    while (len > 0) {
        *dst++ = *src++;
        --len;
    }
    return begin;
}
