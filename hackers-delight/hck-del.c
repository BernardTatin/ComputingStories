/*
 * hck-del.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 12
 */

/*
 * hck-del.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 12
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "hck-del.h"

#if (BITS == 128)
// not sure it's optimal
static inline bool divm(const INT a, const INT b,
                        INT *d, INT *m) {
    if (a == (INT)0) {
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
static char *i128_to_char(const INT N) {
    char *r0 = (char *) malloc(istrl);
    char *r = r0 + istrl - 1;

    if (N == 0) {
        *r0 = '0';
        *(r0 + 1) = 0;
    } else {
        INT d = 0;
        INT m = 0;
        INT n = N;
        bool is_neg = false;
        if (N < 0) {
            is_neg = true;
        }

        memset(r0, ' ', istrl);
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

static char *strip_left(char *ps) {
    char *s = ps;
    while (*s == ' ') {
        s++;
    }
    return strdup(s);
}
#endif

char *int_to_str(const INT n) {
#if (BITS < 128)
    char buffer[istrl];
#if (BITS < 64)
    sprintf(buffer, "%d", n);
#elif (BITS == 64)
    sprintf(buffer, "%ld", n);
#endif
    return strdup(buffer);
#else
    char *r = i128_to_char(n);
    char *s = strip_left(r);
    free(r);
    return strdup(s);
#endif
}

bool sa_add(const INT x, const INT y, INT *result) {
    INT s = x + y;
    *result = s;
    if (has_add_overflow_s(s, x, y)) {
        return false;
    } else {
        return true;
    }
}

bool sa_fibo(const INT n, INT *rfibo) {
    switch(n) {
        case 0:
            return 0;
        case 1:
        case 2:
            return 1;
        default:
            break;
    }
    INT result = 1;
    INT n1 = 1, n2 = 1;
    for (INT i=2; i<n; i++) {
        result = n1 + n2;
        if (has_add_overflow_s(result, n1, n2)) {
            return false;
        } else {
            n1 = n2;
            n2 = result;
        }
    }
    *rfibo = result;
    return true;
}
