/*
 * tfibo.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 16
 */

#include <stdio.h>
#include <stdlib.h>

#include "safe-int-arith.h"
#include "testing.h"

static CONS_FUNC TSAOverflow sa_sfibo(const SA_INT n, SA_INT *rfibo) {
    switch(n) {
        case 0:
            *rfibo = 0;
            return SA_OVF_OK;
        case 1:
        case 2:
            *rfibo = -1;
            return SA_OVF_OK;
        default:
            break;
    }
    SA_INT      result = 1;
    SA_INT      n1     = -1, n2 = 1;
    for (SA_INT i      =2; i < n; i++) {
        result = n1 - n2;
        if (sa_has_sub_overflow_s(result, n1, n2)) {
            return SA_OVF_OVERFLOW;
        } else {
            n1 = n2;
            n2 = result;
        }
    }
    *rfibo = result;
    return SA_OVF_OK;
}

static void exec_test_fibo_r(
		TSAOverflow (*sa_fibo)(const SA_INT n, SA_INT *result),
        char *prompt) {
    SA_INT n      = 0;
    SA_INT result = 0;
	fprintf(stdout, "exec_test_fibo_r with prompt <%s>\n", prompt);
    while (sa_fibo(n, &result) == SA_OVF_OK) {
        char *sn = sa_int_to_str(n);
        char *sr = sa_int_to_str(result);
        fprintf(stdout, "%s fibo %s = %s\n", prompt, sn, sr);
        free(sr);
        free(sn);
        n++;
    }
}

void test_fibo() {
    fprintf(stdout, "test_fibo() ...\n");
    exec_test_fibo_r(sa_fibo, ". ");
    exec_test_fibo_r(sa_fibo_r, "r ");
}

void test_sfibo() {
    SA_INT r = 0;
    SA_INT k = 0;
    while (sa_sfibo(k, &r) == SA_OVF_OK) {
        char *sk = sa_int_to_str(k);
        char *sr = sa_int_to_str(r);
        fprintf(stdout, "sfibo(%4s) = %40s\n", sk, sr);
        free(sr);
        free(sk);
        k++;
    }
}
