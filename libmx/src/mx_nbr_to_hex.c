#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long size = 0, tmp = nbr;
    char symb[] = {'0', '1', '2', '3', '4', '5', '6', '7',  
                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    while (tmp) {
        size++;
        tmp /= 16;
    }

    char *result = mx_strnew(size);

    while (nbr) {
        result[--size] = symb[nbr % 16];
        nbr /= 16;
    }

    return result;
}

