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

#include "hck-del.h"

// mainly for tests
# if (BITS == 4) || (BITS == 8)
SCONST int  count     = 1 << BITS;
#else
SCONST INT count      = 256;
#endif

bool add_overflow_reference(INT x, INT y) {
    return (((x > 0) &
             (y > 0) &
             (x > (imax - y))) |
            ((x < 0) &
             (y < 0) &
             (x < (imin - y)))
    );
}

bool add_overflow_v2(INT x, INT y) {
    return (all_positive(x, y) && (x > (imax - y))) || (all_negative(x, y) && (x < (imin - y)))
    ;
}

#if (BITS == 4)

void show_overflow(bool add_overflow(INT x, INT y)) {
    INT x = imin;

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
    x = imin;
    for (int i = 0; i < count; i++, x++) {
        INT y = imin;
        printf("%2d |", x);
        for (int j = 0; j < count; j++, y++) {
            bool r = add_overflow(y, x);
            INT  s = x + y;
            if (r) {
                printf(" %3s |", " ");
            } else {
                printf(" %3d |", s);
            }
        }
        printf("\n");
    }
}

void experiment_bool(bool add_overflow(INT x, INT y), bool bool_expression(INT x, INT y)) {
    INT x = imin;

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
    x = imin;
    for (int i = 0; i < count; i++, x++) {
        INT y = imin;
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

void experiment_int(bool add_overflow(INT x, INT y), INT int_expression(INT x, INT y)) {
    INT x = imin;

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
    x = imin;
    for (int i = 0; i < count; i++, x++) {
        INT y = imin;
        printf("%2d |", x);
        for (int j = 0; j < count; j++, y++) {
            bool r = add_overflow(y, x);
            INT e = int_expression(y, x);

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
void show_overflow(bool add_overflow(INT x, INT y)) {
    INT x = imin;

    for (int i=0; i<count; i++, x++) {
        INT y = imin;
        for (int j=0; j<count; j++, y++) {
            bool r = add_overflow(x, y);
            char *sx = int_to_str(x);
            char *sy = int_to_str(y);
            fprintf(stdout, "%-3s + %-3s -> %s\n",
                    sx, sy, r ? "ovf" : ":");
            free(sy);
            free(sx);
        }
    }
}
void experiment_bool(bool add_overflow(INT x, INT y), bool bool_expression(INT x, INT y)) {

}
void experiment_int(bool add_overflow(INT x, INT y), INT int_expression(INT x, INT y)) {

}
#endif

INT iexp1(INT x, INT y) {
    INT r1 = (x + y) ^ x;
    INT r2 = (x + y) ^ y;

#if (BITS == 4)
    return (r1 & r2) + imin;
#else
    return r1 & r2;
#endif
}

void test_fibo() {
    INT n = 1;
    INT result = 0;
    while (sa_fibo(n, &result)) {
        char *sn = int_to_str(n);
        char *sr = int_to_str(result);
        fprintf(stdout, "fibo(%6s) = %40s\n", sn, sr);
        free(sn);
        free(sr);
        n++;
    }
}

int main() {
    test_fibo();
    return 0;
}
