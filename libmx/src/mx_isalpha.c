#include "libmx.h"

bool mx_isalpha(char c) {
    if ((c >= 'A' && c <= 'Z') 
        || (c >= 'a' && c <= 'z')) {
        return true;
    }
    return false;
}
