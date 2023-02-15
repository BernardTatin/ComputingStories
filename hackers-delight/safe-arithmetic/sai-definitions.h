/*
 * sai-definitions.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */

/*
 * sai-definitions.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */


#ifndef HACKERS_DELIGHT_SAI_DEFINITIONS_H
#define HACKERS_DELIGHT_SAI_DEFINITIONS_H

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

#endif //HACKERS_DELIGHT_SAI_DEFINITIONS_H
