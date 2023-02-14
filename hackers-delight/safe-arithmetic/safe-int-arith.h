/*
 * safe_int_arith.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 12
 */


#ifndef HACKERS_DELIGHT_SAFE_INT_ARITH_H
#define HACKERS_DELIGHT_SAFE_INT_ARITH_H

#include <stdint.h>
#include "compat.h"

#if !defined(BITS)
#define BITS     128
#endif

#if (BITS == 128)
typedef __int128 SA_INT;
typedef __int128 SA_UINT;
SCONST SA_INT sa_imax  = ((SA_INT)INT64_MAX << 64) | ((SA_INT)UINT64_MAX);
SCONST SA_INT sa_imin  = sa_imax + 1;
SCONST int    sa_istrl = 45;
#elif (BITS == 64)
typedef int64_t  SA_INT;
typedef uint64_t SA_UINT;
SCONST SA_INT sa_imax = INT64_MAX;
SCONST SA_INT sa_imin = INT64_MIN;
SCONST int    sa_istrl = 22;
#elif (BITS == 32)
typedef int32_t  SA_INT;
typedef uint32_t SA_UINT;
SCONST SA_INT sa_imax = INT32_MAX;
SCONST SA_INT sa_imin = INT32_MIN;
SCONST int    sa_istrl = 14;
#elif (BITS == 16)
typedef int16_t  SA_INT;
typedef uint16_t SA_UINT;
SCONST SA_INT sa_imax = INT16_MAX;
SCONST SA_INT sa_imin = INT16_MIN;
SCONST int    sa_istrl = 7;
#elif (BITS == 8)
typedef int8_t  SA_INT;
typedef uint8_t SA_UINT;
SCONST SA_INT sa_imax = INT8_MAX;
SCONST SA_INT sa_imin = INT8_MIN;
SCONST int    sa_istrl = 5;
#elif (BITS == 4)
typedef int8_t  SA_INT;
typedef uint8_t SA_UINT;
SCONST SA_INT sa_imax  = 7;
SCONST SA_INT sa_imin  = -8;
SCONST int    sa_istrl = 5;
#else
    #error "BITS must be one of 4, 8, 16, 32, 64 or 128"
#endif

SCONST SA_UINT sa_hbit      = (SA_UINT) 1 << (BITS - 1);
SCONST SA_INT  sa_bits_mask = -1;

INLINE CONS_FUNC bool sa_2_negative(const SA_INT x, const SA_INT y) {
    SA_INT r = x & y & sa_hbit;
    return r != 0;
}

INLINE CONS_FUNC bool sa_2_positive(const SA_INT x, const SA_INT y) {
    SA_INT r = (x | y) & sa_hbit;
    return r == 0;
}

INLINE CONS_FUNC bool sa_has_add_overflow(const SA_INT x, const SA_INT y) {
    SA_INT s  = x + y;
    SA_INT r1 = s ^ x;
    SA_INT r2 = s ^ y;
    return (r1 & r2 & sa_hbit) != 0;
}

INLINE CONS_FUNC bool sa_has_add_overflow_s(const SA_INT s, const SA_INT x, SA_INT y) {
    SA_INT r1 = s ^ x;
    SA_INT r2 = s ^ y;
    return (r1 & r2 & sa_hbit) != 0;
}

CONS_FUNC char *sa_int_to_str(const SA_INT n);
CONS_FUNC bool sa_add(const SA_INT x, const SA_INT y, SA_INT *result);

CONS_FUNC bool sa_fibo(const SA_INT n, SA_INT *result);

#endif //HACKERS_DELIGHT_SAFE_INT_ARITH_H
