/*
 * int128.c
 *
 * project: PackCC-calc
 * author:  bernard
 * date:    2023 - 02 - 09
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "int128.h"

// not sure it's optimal
static inline bool divm(const __int128 a, const __int128 b,
                        __int128 *d, __int128 *m) {
    if (a == (__int128)0) {
        return false;
    } else if (a < 10 && a >= 0) {
        *d = 0;
        *m = a;
        return true;
    } else {
        *d = a / b;
        *m = a %b;
        if (*m < 0) {
            *m = -(*m);
        }
        return true;
    }
}

// not sure it's optimal
CONS_FUNC char *i128_to_char(const Cint N) {
    char *r0 = (char *) malloc(I128_LEN);
    char *r = r0 + I128_LEN - 1;

    if (N == 0) {
        *r0 = '0';
        *(r0 + 1) = 0;
    } else {
        __int128 d = 0;
        __int128 m = 0;
        __int128 n = N;
        bool is_neg = false;
        if (N < 0) {
            is_neg = true;
        }

        memset(r0, ' ', I128_LEN);
        *(r--) = 0;
        while (divm(n, 10, &d, &m)) {
            char c = (char)m | 0x30;
            *(r--) = c;
            n = d;
        }
        if (is_neg) {
            *(r--) = '-';
        }
    }
    return r0;
}
