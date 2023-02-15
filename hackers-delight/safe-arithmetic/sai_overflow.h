/*
 * sai_overflow.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */

/**
 * Notes
 *
 * ADD OVERFLOW:
 * sa_has_add_overflow_s is quicker than sa_add_overflow_reference
 * timings give a performance gain of 6% to 7%
 * with a lot of calculations (128 bits integers)
 *
 */



#ifndef HACKERS_DELIGHT_SAI_OVERFLOW_H
#define HACKERS_DELIGHT_SAI_OVERFLOW_H

/**
 * enable testing the return value
 * I dare that most functions returns only one of the 2 first values only
 */
typedef enum {
    SA_OVF_OK,          // no overflow/underflow
    SA_OVF_OVERFLOW,    // overflow occurs
    SA_OVF_UNDERFLOW    // underflow occurs
} TSAOverflow;

/**
 * Checks if an overflow can occur when adding two integers, optimized version
 * @param s : the already computed value of x + y,
 * @param x : left operand of addition
 * @param y : right operand of addition
 * @return  : true if an overflow can occur
 */
INLINE CONS_FUNC bool sa_has_add_overflow_s(const SA_INT s, const SA_INT x, SA_INT y) {
    SA_INT r1 = s ^ x;
    SA_INT r2 = s ^ y;
    return (r1 & r2 & sa_hbit) != 0;
}

/**
 * Checks if an overflow can occur when adding two integers, optimized version
 * @param x : left operand of addition
 * @param y : right operand of addition
 * @return  : true if an overflow can occur
 */
INLINE CONS_FUNC bool sa_has_add_overflow(const SA_INT x, const SA_INT y) {
    SA_INT s  = x + y;
    return sa_has_add_overflow_s(s, x, y);
}

/**
 * Checks if an overflow can occur when adding two integers, classic version
 * (for performance testing/debug purpose)
 * @param x : left operand of addition
 * @param y : right operand of addition
 * @return  : true if an overflow can occur
 */
INLINE CONS_FUNC bool sa_add_overflow_reference(SA_INT x, SA_INT y) {
    return (((x > 0) &
             (y > 0) &
             (x > (sa_imax - y))) |
            ((x < 0) &
             (y < 0) &
             (x < (sa_imin - y)))
    );
}

/**
 * An addition which take care of overflow
 * @param x : left operand of addition
 * @param y : right operand of addition
 * @param result : addition result
 * @return  : one of SA_OVF_OVERFLOW, SA_OVF_OK
 */
INLINE CONS_FUNC TSAOverflow sa_add(const SA_INT x, const SA_INT y, SA_INT *result) {
    SA_INT s = x + y;
    *result = s;
    if (sa_has_add_overflow_s(s, x, y)) {
        return SA_OVF_OVERFLOW;
    } else {
        return SA_OVF_OK;
    }
}

#endif //HACKERS_DELIGHT_SAI_OVERFLOW_H
