#include "libmx.h"

void mx_printint(int n) {
    char number[10];
    int length = 0;
    long res_n = n; // to fix overflow int -2147483648
    if (n == 0) {
        mx_printchar('0');
    }
    if (res_n < 0) {
        mx_printchar('-');
        res_n *= -1;
    }
    while (res_n != 0) {
        number[length++] = '0' + res_n % 10;
        res_n /= 10;
    }
    while (length > 0) {
        mx_printchar(*(number + length -1));
        --length;
    }
}

