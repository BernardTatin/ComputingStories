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

INLINE CONS_FUNC bool divm10(const SA_INT a,
                        SA_INT *d, SA_INT *m) {
    const SA_INT b = 10;
    if (a == (SA_INT)0) {
        return false;
    } else if (a < 10) {
        *d = 0;
        *m = a;
        return true;
    } else {
        *d = a / b;
        *m = a %b;
        return true;
    }
}

static const char decimals[] = "0123456789";
// Optimization: cf https://tia.mat.br/posts/2014/06/23/integer_to_string_conversion.html
static CONS_FUNC char *kern_istr(const SA_INT N) {
    char r0[sa_istrl + 1];
    char *r = r0 + sa_istrl - 1;
    SA_INT d      = 0;
    SA_INT m      = 0;
    SA_INT n      = N;
    bool   is_neg = false;

    if (N < 0) {
        is_neg = true;
        n = -n;
    }

    *r = 0;
    while (divm10(n, &d, &m)) {
        char c = decimals[(int)m];
        *(--r) = c;
        n = d;
    }
    if (is_neg) {
        *(--r) = '-';
    }
    size_t delta = (size_t)(r - r0);
    return strdup(r0 + delta);
}


CONS_FUNC char *sa_int_to_str(const SA_INT n) {
    if (n == 0) {
        return strdup("0");
    } else {
        return kern_istr(n);
    }
}
