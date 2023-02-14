/*
 * safe_int_arith.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 12
 */

#include <stdio.h>
#include <string.h>

#include "safe-int-arith.h"

#if (BITS < 128)
CONS_FUNC char *sa_int_to_str(const SA_INT n) {
    char buffer[sa_istrl];
#if (BITS < 64)
    sprintf(buffer, "%d", n);
#elif (BITS == 64)
    sprintf(buffer, "%ld", n);
#endif
    return strdup(buffer);
}
#endif

CONS_FUNC bool sa_add(const SA_INT x, const SA_INT y, SA_INT *result) {
    SA_INT s = x + y;
    *result = s;
    if (sa_has_add_overflow_s(s, x, y)) {
        return false;
    } else {
        return true;
    }
}

CONS_FUNC bool sa_fibo(const SA_INT n, SA_INT *rfibo) {
    switch(n) {
        case 0:
            return 0;
        case 1:
        case 2:
            return 1;
        default:
            break;
    }
    SA_INT      result = 1;
    SA_INT      n1     = 1, n2 = 1;
    for (SA_INT i      =2; i < n; i++) {
        result = n1 + n2;
        if (sa_has_add_overflow_s(result, n1, n2)) {
            return false;
        } else {
            n1 = n2;
            n2 = result;
        }
    }
    *rfibo = result;
    return true;
}
