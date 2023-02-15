/*
 * sai-maths.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */

#include "safe-int-arith.h"

CONS_FUNC TSAOverflow sa_fibo(const SA_INT n, SA_INT *rfibo) {
    switch(n) {
        case 0:
            *rfibo = 0;
            return SA_OVF_OK;
        case 1:
        case 2:
            *rfibo = 1;
            return SA_OVF_OK;
        default:
            break;
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
