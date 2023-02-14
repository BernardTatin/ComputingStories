/*
 * safe-128b-arith.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 14
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "safe-int-arith.h"

#if (BITS == 128)
// not sure it's optimal
INLINE CONS_FUNC bool divm(const SA_INT a, const SA_INT b,
                        SA_INT *d, SA_INT *m) {
    if (a == (SA_INT)0) {
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
static CONS_FUNC char *i128_to_char(const SA_INT N) {
    char *r0 = (char *) malloc(sa_istrl);
    char *r = r0 + sa_istrl - 1;

    if (N == 0) {
        *r0 = '0';
        *(r0 + 1) = 0;
    } else {
        SA_INT d      = 0;
        SA_INT m      = 0;
        SA_INT n      = N;
        bool   is_neg = false;
        if (N < 0) {
            is_neg = true;
        }

        memset(r0, ' ', sa_istrl);
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

static CONS_FUNC char *strip_left(char *ps) {
    char *s = ps;
    while (*s == ' ') {
        s++;
    }
    return strdup(s);
}

CONS_FUNC char *sa_int_to_str(const SA_INT n) {
    char *r = i128_to_char(n);
    char *s = strip_left(r);

    free(r);
    return strdup(s);
}

#endif
