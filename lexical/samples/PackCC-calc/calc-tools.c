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

CONS_FUNC char *str_strip_left(char *s) {
    char *r = s;

    while (*r == ' ') {
        r++;
    }
    return r;
}

static inline bool divm(const __int128 a, const __int128 b,
                        __int128 *d, __int128 *m) {
    if (a == (__int128)0) {
        return false;
    } else if (a > 0) {
        *d = a / b;
        *m = a %b;
        return true;
    } else {
        return divm(-a, b, d, m);
    }
}

CONS_FUNC char *i128_to_char(const __int128 N) {
    char *r0 = (char *) malloc(I128_LEN);
    char *r = r0 + I128_LEN - 1;

    if (N == 0) {
        *r0 = '0';
        *(r0 + 1) = 0;
    } else {
        __int128 d = 0;
        __int128 m = 0;
        __int128 n = N;

        memset(r0, ' ', I128_LEN);
        *(r--) = 0;
        while (divm(n, 10, &d, &m)) {
            char c = (char)m | 0x30;
            *(r--) = c;
            n = d;
        }
        if (N < 0) {
            *(r--) = '-';
        }
    }
    return r0;
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
		result = n1 + n2;
		n1 = n2;
		n2 = result;
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

int main(int argc, char **argv) {
    bool quiet = false;

    if (argc == 2) {
        if (strcmp(argv[1], "-q") == 0) {
            quiet = true;
        }
    }
    if (!quiet) {
        printf("\nsuper calc, version %s (%s)\n\n", calc_version, __DATE__);
		test_int_size();
        printf("%s ", PROMPT_USER);
    }

    parse(quiet);

    if (!quiet) {
        printf("\n");
    }

    return 0;
}
