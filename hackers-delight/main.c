/*
 * main.c
 *
 * project: hackers-delight
 * author:  bernard
 * date:    2023 - 02 - 09
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "safe-arithmetic/safe-int-arith.h"

// mainly for tests
# if (BITS == 4) || (BITS == 8)
SCONST int  count     = 1 << BITS;
#else
SCONST SA_INT count = 256;
#endif


bool add_overflow_v2(SA_INT x, SA_INT y) {
    return (sa_2_positive(x, y) && (x > (sa_imax - y))) || (sa_2_negative(x, y) && (x < (sa_imin - y)))
    ;
}

#if (BITS == 4)

void show_overflow(bool add_overflow(SA_INT x, SA_INT y)) {
    SA_INT x = sa_imin;

    printf("\n");
    for (int i = 0; i < 17; i++) {
        printf("=====");
    }
    printf("\n");
    printf("-- |");
    for (int i = 0; i < count; i++, x++) {
        printf(" %3d |", x);
    }
    printf("\n");
    x = sa_imin;
    for (int i = 0; i < count; i++, x++) {
        SA_INT y = sa_imin;
        printf("%2d |", x);
        for (int j = 0; j < count; j++, y++) {
            bool   r = add_overflow(y, x);
            SA_INT s = x + y;
            if (r) {
                printf(" %3s |", " ");
            } else {
                printf(" %3d |", s);
            }
        }
        printf("\n");
    }
}

void experiment_bool(bool add_overflow(SA_INT x, SA_INT y), bool bool_expression(SA_INT x, SA_INT y)) {
    SA_INT x = sa_imin;

    printf("\n");
    for (int i = 0; i < 17; i++) {
        printf("=====");
    }
    printf("\n");
    printf("-- |");
    for (int i = 0; i < count; i++, x++) {
        printf(" %3d |", x);
    }
    printf("\n");
    x = sa_imin;
    for (int i = 0; i < count; i++, x++) {
        SA_INT y = sa_imin;
        printf("%2d |", x);
        for (int j = 0; j < count; j++, y++) {
            bool r = add_overflow(y, x);
            bool e = bool_expression(y, x);
            char *s = e ? "1" : " ";

            if (r) {
                printf(" <%s> |", s);
            } else {
                printf("  %s  |", s);
            }
        }
        printf("\n");
    }

}

void experiment_int(bool add_overflow(SA_INT x, SA_INT y), SA_INT int_expression(SA_INT x, SA_INT y)) {
    SA_INT x = sa_imin;

    printf("\n");
    for (int i = 0; i < 17; i++) {
        printf("=====");
    }
    printf("\n");
    printf("-- |");
    for (int i = 0; i < count; i++, x++) {
        printf(" %3d |", x);
    }
    printf("\n");
    x = sa_imin;
    for (int i = 0; i < count; i++, x++) {
        SA_INT y = sa_imin;
        printf("%2d |", x);
        for (int j = 0; j < count; j++, y++) {
            bool   r = add_overflow(y, x);
            SA_INT e = int_expression(y, x);

            if (r) {
                printf("<%3d>|", e);
            } else {
                printf(" %3d |", e);
            }
        }
        printf("\n");
    }

}
#else
void show_overflow(bool add_overflow(SA_INT x, SA_INT y)) {
    SA_INT x = sa_imin;

    for (int i=0; i<count; i++, x++) {
        SA_INT   y = sa_imin;
        for (int j =0; j<count; j++, y++) {
            bool r = add_overflow(x, y);
            char *sx = sa_int_to_str(x);
            char *sy = sa_int_to_str(y);
            fprintf(stdout, "%-3s + %-3s -> %s\n",
                    sx, sy, r ? "ovf" : ":");
            free(sy);
            free(sx);
        }
    }
}
void experiment_bool(bool add_overflow(SA_INT x, SA_INT y), bool bool_expression(SA_INT x, SA_INT y)) {

}
void experiment_int(bool add_overflow(SA_INT x, SA_INT y), SA_INT int_expression(SA_INT x, SA_INT y)) {

}
#endif

SA_INT iexp1(SA_INT x, SA_INT y) {
    SA_INT r1 = (x + y) ^ x;
    SA_INT r2 = (x + y) ^ y;

#if (BITS == 4)
    return (r1 & r2) + sa_imin;
#else
    return r1 & r2;
#endif
}

static inline void il_free(char *ptr) {
    //fprintf(stdout, "(                                           .) -- (%s)\n", ptr);
    free(ptr);
}


void test_fibo() {
    SA_INT n      = 1;
    SA_INT result = 0;
    while (sa_fibo(n, &result) == SA_OVF_OK) {
        char *sn = sa_int_to_str(n);
        char *sr = sa_int_to_str(result);
        fprintf(stdout, "fibo(%6s) = %40s\n", sn, sr);
        il_free(sr);
        il_free(sn);
        n++;
    }
}

bool tsub(const SA_INT n, SA_INT *result) {
    SA_INT s = 0;
    bool no_ovf = true;
#if 0
    for (SA_INT i=0; i<n; i++) {
        if (sa_add_overflow_reference(s, n)) {
            no_ovf = false;
            break;
        } else {
            SA_INT ts = s + n;
            s = ts;
        }
    }
#else
    SA_INT x = sa_imax - 2*n;
    for (SA_INT i=0; i<n; i++, x++) {
        SA_INT ts = x - s;
        if (sa_has_sub_overflow_s(ts, x, s)) {
            no_ovf = false;
            break;
        } else {
            char *si = sa_int_to_str(x);
            char *st = sa_int_to_str(ts);

            fprintf(stdout, "%45s -> %45s\n", si, st);
            free(si);
            free(st);
            s = ts;
        }
    }
#endif
    *result = s;
    return no_ovf;
}

bool tsumm(const SA_INT n, SA_INT *result) {
    SA_INT s = 0;
    bool no_ovf = true;
#if 0
    for (SA_INT i=0; i<n; i++) {
        if (sa_add_overflow_reference(s, n)) {
            no_ovf = false;
            break;
        } else {
            SA_INT ts = s + n;
            s = ts;
        }
    }
#else
    for (SA_INT i=0; i<n; i++) {
        SA_INT ts = s + n;
        if (sa_has_add_overflow_s(ts, s, n)) {
            no_ovf = false;
            break;
        } else {
            s = ts;
        }
    }
#endif
    *result = s;
    return no_ovf;
}

#if (BITS < 16)
const SA_INT timax = sa_imax;
#else
const SA_INT timax = 200;
#endif

void test_perf_add_ovf(SA_INT imax) {
    SA_INT r = 0;
    for (SA_INT i=0; i<imax; i++) {
        if (!tsumm(i, &r)) {
            char *si = sa_int_to_str(i);
            fprintf(stdout, "test_perf_add_ovf failed at %s\n", si);
            free(si);
            return;
        }
    }
    char *si = sa_int_to_str(imax);
    fprintf(stdout, "test_perf_add_ovf works until %s\n", si);
    free(si);
}

CONS_FUNC TSAOverflow sa_sfibo(const SA_INT n, SA_INT *rfibo) {
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
void test_perf_sub_ovf(SA_INT imax) {
    SA_INT r = sa_imin;
    for (SA_INT i=0; i<imax; i++) {
        if (!tsub(i, &r)) {
            char *si = sa_int_to_str(i);
            fprintf(stdout, "test_perf_sub_ovf failed at %s\n", si);
            free(si);
            //return;
        }
    }
    char *si = sa_int_to_str(imax);
    fprintf(stdout, "test_perf_sub_ovf tested until %s\n", si);
    free(si);
}

void test_print128bits(const int count) {
    SA_INT n1 = sa_imin, n2 = 0;
    for (int i=0; i<count; i++, n1++, n2++) {
        char *s1 = sa_int_to_str(n1);
        char *s2 = sa_int_to_str(n2);
        fprintf(stdout, "%-45s %-45s\n", s1, s2);
        free(s1);
        free(s2);
    }
}
int main() {
#if 0
    test_print128bits(4600);
#else
    test_sfibo();
#endif
    return 0;
}
