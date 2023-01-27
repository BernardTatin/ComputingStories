/*
 * calc-tools.c
 * 26/01/2023
 * bernard T.
 */

#include <stdio.h>
#include "calc-tools.h"


int gcd(const int a, const int b) {
	if (b == 0) {
		return a;
	} else  {
		__attribute__((musttail))	return gcd(b, a % b);
	}
}
