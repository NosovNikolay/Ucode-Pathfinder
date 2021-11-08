#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int index = 0;
    int sub_len = 0;

    if (!sub || !str) {
        return -2;
    }
    sub_len = mx_strlen(sub);
    while (*str) {
        if (mx_strncmp(str, sub, sub_len) == 0) {
            return index;
        }
        index++;
        str++;
    }

    return -1;
}
