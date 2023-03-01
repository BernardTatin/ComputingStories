/*
 * compat.h
 * 08/02/2023
 * bernard T.
 */

#if !defined(__COMPAT_H__)
#define __COMPAT_H__

#if defined(__clang__)
    #define COMPAT_CLANG
#elif defined(__GNUC__)
    #define COMPAT_GCC
#endif

#include <stdbool.h>

//  these attributes are dangerous, mostly with gcc
// use them with caution
#if defined(COMPAT_CLANG)   // || defined(COMPAT_GCC)
    #define PURE_FUNC __attribute__((pure))
    #define CONS_FUNC __attribute__((const))
#else
    #define PURE_FUNC
    #define CONS_FUNC
#endif

#if defined(COMPAT_CLANG)
#define MUSTTAIL	__attribute__((musttail))
#else
#define MUSTTAIL
#endif

#if !defined(SCONST)
#define SCONST static const
#endif

#if !defined(INLINE)
#define INLINE static inline
#endif

#endif
