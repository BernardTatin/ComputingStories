/*
 * calc-tools.c
 * 26/01/2023
 * bernard T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "calc-tools.h"
#include "calc.h"
#include "compat.h"

CONS_FUNC char *str_strip_left(char *s) {
    char *r = s;

    while (*r == ' ') {
        r++;
    }
    return r;
}

CONS_FUNC Cint gcd(const Cint a, const Cint b) {
	if (b == 0) {
		return a;
	} else  {
		__attribute__((musttail))	return gcd(b, a % b);
	}
}

CONS_FUNC Cint fact(const Cint n) {
	Cint r = 1;
	if (n > (Cint)1) {
		for (Cint i=(Cint)2; i<=n; i++) {
			r *= i;
		}
	}
	return r;
}

CONS_FUNC Cint fibo(const Cint n) {
	switch (n) {
		case 0:
			return 0;
		case 1:
		case 2:
			return 1;
		default:
			break;
	}
	Cint result = 1;
	Cint n1 = 1, n2 = 1;
	for (Cint i=2; i<n; i++) {
        if (s_add(n1, n2, &result)) {
            n1 = n2;
            n2 = result;
        } else {
            fprintf(stderr, "ADD Overflow\n");
            result = 0;
            break;
        }
	}
	return result;
}

CONS_FUNC CalcConfig *create_auxiliary(const bool is_quiet) {
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

CONS_FUNC void destroy_auxiliary(CalcConfig *conf) {
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

#define SHOWS(t)	fprintf(stdout, "size of %-10s : %3zu\n", #t, sizeof(t))
static void test_int_size() {
	SHOWS(short);
	SHOWS(int);
	SHOWS(long);
	SHOWS(long long);
#undef SHOWS
}

static void test_min_max() {
    Cint maxH = (Cint)INT64_MAX;
    Cint maxL = (Cint)UINT64_MAX;
    Cint max = (maxH << 64) | maxL;
    Cint min = max + 1;

    char *smax = i128_to_char(max);
    char *smin = i128_to_char(min);

    fprintf(stdout, "i128 max: %s\n", smax);
    // I can't print it
    fprintf(stdout, "i128 min: %s\n", smin);
}

int main(int argc, char **argv) {
    bool quiet = false;

    if (argc == 2) {
        if (strcmp(argv[1], "-q") == 0) {
            quiet = true;
        }
    }
    if (!quiet) {
        printf("\nSuper %s, version %s (%s)\n\n", CALC_NAME, calc_version, __DATE__);
		test_int_size();
        test_min_max();
        printf("%s ", PROMPT_USER);
    }

    parse(quiet);

    if (!quiet) {
        printf("\n");
    }

    return 0;
}
