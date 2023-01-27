/*
 * calc-tools.h
 * 26/01/2023
 * bernard T.
 */

#if !defined(__CALC_TOOLS_H__)

#include <string.h>

#define calc_version "0.0.2"
#define PROMPT_USER ">:"
#define PROMPT_CALC ">="

static inline char last_char(const char *s) {
	size_t l = strlen(s);
	return s[l - 1];
}

static inline void show_result(const int result, const char *line) {
	char c = last_char(line);
	if (c != ';') {
		printf("%s %6d\n%s ",
				PROMPT_CALC, result, PROMPT_USER);
	} else {
		printf("%s %6d; ", PROMPT_CALC, result);
	}
}

int gcd(const int a, const int b)  __attribute__((pure));

#endif // __CALC_TOOLS_H__
