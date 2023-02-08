/*
 * calc-tools.h
 * 26/01/2023
 * bernard T.
 */

#if !defined(__CALC_TOOLS_H__)
#define  __CALC_TOOLS_H__

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "compat.h"

#if defined(COMPAT_128B_INT)
    typedef COMPAT_128B_INT Cint;
    #define CALC_NAME "Calc (128 bits integers)"
#else
    typedef int64_t Cint
    #define CALC_NAME "Calc (64 bits integers)"
#endif

#define calc_version "0.0.3"
#define PROMPT_USER ">:"
#define PROMPT_CALC ">="
#define PROMPT_EMPTY ""

#define MAXLEN	    256
#define I128_LEN    128

typedef struct _CalcConfig {
	bool is_quiet;
	char *prompt_user;
	char *prompt_calc;
	char r0[MAXLEN+1];
	size_t s0e;
	size_t s0s;

} CalcConfig;

CONS_FUNC char *i128_to_char(const Cint);
CONS_FUNC char *str_strip_left(char *s);

static inline void show_result(const Cint N, const char eol, const bool is_quiet) {
    char *N_str = i128_to_char(N);
    char *result = str_strip_left(N_str);

	if (is_quiet) {
		if (eol != ';') {
			printf("%s\n", result);
		} else {
			printf("%s; ", result);
		}
	} else {
		if (eol != ';') {
			printf("%s %16s\n%s ",
					PROMPT_CALC, result, PROMPT_USER);
		} else {
			printf("%s %616s; ", PROMPT_CALC, result);
		}
	}
    free(N_str);
}

CONS_FUNC Cint gcd(const Cint a, const Cint b);
CONS_FUNC Cint fact(const Cint n);
CONS_FUNC Cint fibo(const Cint n);
CONS_FUNC CalcConfig *create_auxiliary(const bool is_quiet);
CONS_FUNC void destroy_auxiliary(CalcConfig *conf);
void parse(const bool is_quiet);

#endif // __CALC_TOOLS_H__
