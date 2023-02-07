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

#define PURE_FUNC __attribute__((pure))
#define CONS_FUNC __attribute__((const))

typedef int64_t Cint;

#define calc_version "0.0.2"
#define PROMPT_USER ">:"
#define PROMPT_CALC ">="
#define PROMPT_EMPTY ""

#define MAXLEN	256

typedef struct _CalcConfig {
	bool is_quiet;
	char *prompt_user;
	char *prompt_calc;
	char r0[MAXLEN+1];
	size_t s0e;
	size_t s0s;

} CalcConfig;

static inline void show_result(const Cint result, const char eol, const bool is_quiet) {
	if (is_quiet) {
		if (eol != ';') {
			printf("%ld\n", result);
		} else {
			printf("%ld; ", result);
		}
	} else {
		if (eol != ';') {
			printf("%s %6ld\n%s ",
					PROMPT_CALC, result, PROMPT_USER);
		} else {
			printf("%s %6ld; ", PROMPT_CALC, result);
		}
	}
}

CONS_FUNC Cint gcd(const Cint a, const Cint b);
CONS_FUNC Cint fact(const Cint n);
CONS_FUNC Cint fibo(const Cint n);
CONS_FUNC CalcConfig *create_auxiliary(const bool is_quiet);
CONS_FUNC void destroy_auxiliary(CalcConfig *conf);
void parse(const bool is_quiet);

#endif // __CALC_TOOLS_H__
