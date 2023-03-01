/*
 * tstrings.c
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 16
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "safe-int-arith.h"
#include "testing.h"

void test_print_bits(const int count) {
    SA_INT n1 = sa_imin, n2 = 0;
    for (int i=0; i<count; i++, n1++, n2++) {
        char *s1 = sa_int_to_str(n1);
        char *s2 = sa_int_to_str(n2);
        fprintf(stdout, "%-45s %-45s\n", s1, s2);
        free(s1);
        free(s2);
    }
}
