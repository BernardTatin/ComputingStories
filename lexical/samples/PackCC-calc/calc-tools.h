/*
 * calc-tools.h
 * 26/01/2023
 * bernard T.
 */

#if !defined(__CALC_TOOLS_H__)

#include <stdbool.h>
#include <string.h>

#define calc_version "0.0.2"
#define PROMPT_USER ">:"
#define PROMPT_CALC ">="
#define PROMPT_EMPTY ""

typedef struct _CalcConfig {
	bool is_quiet;
	char *prompt_user;
	char *prompt_calc;
} CalcConfig;

static inline char last_char(const char *s) __attribute__((pure)) {
	size_t l = strlen(s);
	return s[l - 1];
}

static inline void show_result(const int result, const char *line, const bool is_quiet) {
	char c = last_char(line);
	if (is_quiet) {
		if (c != ';') {
			printf("%d\n", result);
		} else {
			printf("%d; ", result);
		}
	} else {
		if (c != ';') {
			printf("%s %6d\n%s ",
					PROMPT_CALC, result, PROMPT_USER);
		} else {
			printf("%s %6d; ", PROMPT_CALC, result);
		}
	}
}

int gcd(const int a, const int b)  __attribute__((pure));

CalcConfig *create_auxiliary(const bool is_quiet);
void destroy_auxiliary(CalcConfig *conf);
void parse(const bool is_quiet);

#endif // __CALC_TOOLS_H__
