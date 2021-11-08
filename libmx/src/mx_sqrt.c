#include "libmx.h"
static double double_abs(double num) {
    return num >= 0.0 ? num : -num;
}

static int get_result(double guess, double eps) {
    if ((guess - (int)guess) > eps) {
        return 0;
    }

    return (int)guess;
}

int mx_sqrt(int x) {
    double number = x;
    double guess = 0;
    double eps = 0.000001;

    if (x <= 0) {
        return 0;
    }

    while (1) {
        guess = 0.5 * (number + x / number);

        if (double_abs(guess - number) < eps) {
            break;
        }

        number = guess;
    }

    return get_result(guess, eps);
}


