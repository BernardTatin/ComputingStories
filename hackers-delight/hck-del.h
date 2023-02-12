/*
 * hck-del.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 12
 */


#ifndef HACKERS_DELIGHT_HCK_DEL_H
#define HACKERS_DELIGHT_HCK_DEL_H

#if !defined(SCONST)
#define SCONST static const
#endif

#if !defined(INLINE)
#define INLINE static inline
#endif


#if !defined(BITS)
#define BITS    128
#endif

#if (BITS == 128)
typedef __int128 INT;
typedef __int128 UINT;
SCONST INT imax = ((INT)INT64_MAX << 64) | ((INT)UINT64_MAX);
SCONST INT imin = imax + 1;
SCONST int istrl = 45;
#elif (BITS == 64)
typedef int64_t  INT;
typedef uint64_t UINT;
SCONST INT imax = INT64_MAX;
SCONST INT imin = INT64_MIN;
SCONST int istrl = 22;
#elif (BITS == 32)
typedef int32_t  INT;
typedef uint32_t UINT;
SCONST INT imax = INT32_MAX;
SCONST INT imin = INT32_MIN;
SCONST int istrl = 14;
#elif (BITS == 16)
typedef int16_t  INT;
typedef uint16_t UINT;
SCONST INT imax = INT16_MAX;
SCONST INT imin = INT16_MIN;
SCONST int istrl = 7;
#elif (BITS == 8)
typedef int8_t  INT;
typedef uint8_t UINT;
SCONST INT imax = INT8_MAX;
SCONST INT imin = INT8_MIN;
SCONST int istrl = 5;
#elif (BITS == 4)
typedef int8_t  INT;
typedef uint8_t UINT;
SCONST INT imax = 7;
SCONST INT imin = -8;
SCONST int istrl = 5;
#else
    #error "BITS must be one of 4, 8, 16, 32, 64 or 128"
#endif

SCONST UINT hbit_mask = (UINT) 1 << (BITS - 1);
SCONST INT bits_mask  = -1;

INLINE bool all_negative(const INT x, const INT y) {
    INT r = x & y & hbit_mask;
    return r != 0;
}

INLINE bool all_positive(const INT x, const INT y) {
    INT r = (x | y) & hbit_mask;
    return r == 0;
}

INLINE bool has_add_overflow(const INT x, const INT y) {
    INT s = x + y;
    INT r1 = s ^ x;
    INT r2 = s ^ y;
    return (r1 & r2 & hbit_mask) != 0;
}

INLINE bool has_add_overflow_s(const INT s, const INT x, INT y) {
    INT r1 = s ^ x;
    INT r2 = s ^ y;
    return (r1 & r2 & hbit_mask) != 0;
}

char *int_to_str(const INT n);
bool sa_add(const INT x, const INT y, INT *result);

bool sa_fibo(const INT n, INT *result);

#endif //HACKERS_DELIGHT_HCK_DEL_H
