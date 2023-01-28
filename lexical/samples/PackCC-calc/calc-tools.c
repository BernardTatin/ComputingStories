/*
 * calc-tools.c
 * 26/01/2023
 * bernard T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calc-tools.h"


int gcd(const int a, const int b) {
	if (b == 0) {
		return a;
	} else  {
		__attribute__((musttail))	return gcd(b, a % b);
	}
}


CalcConfig *create_auxiliary(const bool is_quiet) {
	CalcConfig *conf = (CalcConfig *)malloc(sizeof(CalcConfig));
	if (conf != NULL) {
		conf->is_quiet = is_quiet;
		if (is_quiet) {
			conf->prompt_user = PROMPT_EMPTY;
			conf->prompt_calc = PROMPT_EMPTY;
		} else {
			conf->prompt_user = PROMPT_USER;
			conf->prompt_calc = PROMPT_CALC;
		}
	}
	return conf;
}

void destroy_auxiliary(CalcConfig *conf) {
	if (conf != NULL) {
		free(conf);
	}
}
