/*
 * compat.h
 * 08/02/2023
 * bernard T.
 */

#if !defined(__COMPAT_H__)
#define __COMPAT_H__

#include <stdint.h>

#if defined(__clang__)
    #define COMPAT_CLANG
#elif defined(__GNUC__)
    #define COMPAT_GCC
#endif


#if defined(__clang__) || defined(__GNUC__)
    #define PURE_FUNC __attribute__((pure))
    #define CONS_FUNC __attribute__((const))
#else
    #define PURE_FUNC
    #define CONS_FUNC
#endif

#endif
