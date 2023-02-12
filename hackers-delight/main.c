/*
 * main.c
 *
 * project: hackers-delight
 * author:  bernard
 * date:    2023 - 02 - 09
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BITS    4

#if (BITS == 4) || (BITS == 8)
typedef int8_t  INT;
typedef uint8_t UINT;
#endif

const size_t isize = BITS;
#if (BITS == 8)
const INT imax = INT8_MAX;
const INT imin = INT8_MIN;
#elif (BITS == 4)
const INT imax = 7;
const INT imin = -8;
#endif

const UINT hbit_mask = (UINT) 1 << (isize - 1);
const int  count     = 1 << BITS;
const int bits_mask = count - 1;

bool all_negative(INT x, INT y) {
    INT r = x & y & hbit_mask;
    return r != 0;
}

bool all_positive(INT x, INT y) {
    INT r = (x | y) & hbit_mask;
    return r == 0;
}

bool add_overflow_v0(INT x, INT y) {
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
void show_overflow() {
    INT x = imin;

    for (int i=0; i<count; i++, x++) {
        INT y = imin;
        for (int j=0; j<count; j++, y++) {
            bool r = add_overflow_v1(x, y);
            fprintf(stdout, "%3d + %3d -> %s\n", x, y, r ? "ovf" : ":");
        }
    }
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

bool add_overflow_good(INT x, INT y) {
    INT s = x + y;
    INT r1 = s ^ x;
    INT r2 = s ^ y;
    return (r1 & r2 & hbit_mask) != 0;
}


int main() {
    show_overflow(add_overflow_v0);
    experiment_bool(add_overflow_v0, all_negative);
    experiment_bool(add_overflow_v0, all_positive);
    show_overflow(add_overflow_v2);
    experiment_int(add_overflow_v0, iexp1);
    show_overflow(add_overflow_good);
    return 0;
}
