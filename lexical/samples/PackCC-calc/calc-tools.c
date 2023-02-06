/*
 * calc-tools.c
 * 26/01/2023
 * bernard T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "calc-tools.h"
#include "calc.h"


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

void parse(const bool is_quiet) {
    CalcConfig *conf = create_auxiliary(is_quiet);
    calc_context_t *ctx = calc_create(conf);
    while (calc_parse(ctx, NULL))
        ;
    destroy_auxiliary(conf);
    calc_destroy(ctx);
}

int main(int argc, char **argv) {
    bool quiet = false;
    if (argc == 2) {
        if (strcmp(argv[1], "-q") == 0) {
            quiet = true;
        }
    }
    if (!quiet) {
        printf("\nsuper calc, version %s (%s)\n\n", calc_version, __DATE__);
        printf("%s ", PROMPT_USER);
    }

    parse(quiet);

    if (!quiet) {
        printf("\n");
    }

    return 0;
}
