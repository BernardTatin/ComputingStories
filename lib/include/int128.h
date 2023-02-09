/*
 * int128.h
 *
 * project: PackCC-calc
 * author:  bernard
 * date:    2023 - 02 - 09
 */


#ifndef PACKCC_CALC_INT128_H
#define PACKCC_CALC_INT128_H

#include <stdbool.h>
#include "compat.h"

#if defined(__SIZEOF_INT128__)

    #define HAS_128BITS_INT
    #define I128_LEN     45

    typedef __int128 Cint;

    static const Cint i128_max = ((Cint)INT64_MAX << 64) | ((Cint)UINT64_MAX);
    static const Cint i128_carry_bit = 1 << 127;

    CONS_FUNC char *i128_to_char(const Cint);

    static inline bool s_add(const Cint a, const Cint b, Cint *r) {
        bool result = true;

    #if 0
        // a big failure! Ouch!
        Cint s = (a ^ i128_carry_bit) + (b ^ i128_carry_bit);
        bool c = (s & i128_carry_bit) !=0;
        bool all_pos = (a > 0) && (b > 0);
        bool all_neg = (a < 0) && (b < 0);
        bool overflow = (c && all_pos) || (!c && all_neg);
        if (!overflow) {
            *r = s;
        } else {
            result = false;
        }

    #else
        if (a < i128_max - b) {
            *r = a + b;
        } else {
            result = false;
        }
    #endif
        return result;
    }
#endif

#endif //PACKCC_CALC_INT128_H
