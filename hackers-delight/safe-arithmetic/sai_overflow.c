/*
 * sai_overflow.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 03 - 01
 */

#include "safe-int-arith.h"

static int inlz(const int shift, const SA_INT k, const int acc) {
    if (shift == 1) {
        if ((k & sa_hbit) == sa_hbit) {
            return acc - 1;
        } else {
            return acc;
        }
    }
    if ((k >> (BITS - shift)) == 0) {
        MUSTTAIL return inlz (shift >> 1, k << shift, acc + shift);
    } else {
        MUSTTAIL return inlz(shift >> 1, k, acc);
    }
}

int nlz(const SA_INT x) {
    if (x == 0) {
        return BITS;
    } else if (x < 0) {
        return inlz(BITS >> 1, -x, 1);
    }
    return inlz(BITS >> 1, x, 1);
}
