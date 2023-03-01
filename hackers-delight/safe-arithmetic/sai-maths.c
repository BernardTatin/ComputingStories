/*
 * sai-maths.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */

#include <stdio.h>
#include "safe-int-arith.h"

CONS_FUNC TSAOverflow sa_fibo(const SA_INT n, SA_INT *rfibo) {
    if (n < (SA_INT)2) {
        *rfibo = n;
        return SA_OVF_OK;
    }
    SA_INT      result = 1;
    SA_INT      n1     = 1, n2 = 1;
    for (SA_INT i      =2; i < n; i++) {
        result = n1 + n2;
        if (sa_has_add_overflow_s(result, n1, n2)) {
            return SA_OVF_OVERFLOW;
        } else {
            n1 = n2;
            n2 = result;
        }
    }
    *rfibo = result;
    return SA_OVF_OK;
}

static TSAOverflow inner_fibo(const int cpt,
                                        const SA_INT n1,
                                        const SA_INT n2,
                                        SA_INT *r) {
    if (cpt == 0) {
        return SA_OVF_OK;
    }
    SA_INT s = n1 + n2;
    if (sa_has_add_overflow_s(s, n1, n2)) {
        return SA_OVF_OVERFLOW;
    }
	*r = s;
	MUSTTAIL return inner_fibo(cpt - 1, n2, s, r);
}

CONS_FUNC TSAOverflow sa_fibo_r(const SA_INT pn, SA_INT *rfibo) {
    int n = (int)pn;
    if (n < (SA_INT)2) {
        *rfibo = n;
        return SA_OVF_OK;
    } else {
        return inner_fibo(n, 0, 1, rfibo);
    }
}
