#include "libmx.h"

void mx_str_reverse(char *s) {
    if (!s) {
        return;
    }
    for (char *end = s + mx_strlen(s) - 1; end > s; --end) {
        mx_swap_char(s, end);
        ++s;
    }
}
