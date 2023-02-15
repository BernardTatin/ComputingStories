/*
 * sai-misc.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */

/*
 * sai-misc.h
 *
 * project: hackers_delight
 * author:  bernard
 * date:    2023 - 02 - 15
 */


#ifndef HACKERS_DELIGHT_SAI_MISC_H
#define HACKERS_DELIGHT_SAI_MISC_H

INLINE CONS_FUNC bool sa_2_negative(const SA_INT x, const SA_INT y) {
    SA_INT r = x & y & sa_hbit;
    return r != 0;
}

INLINE CONS_FUNC bool sa_2_positive(const SA_INT x, const SA_INT y) {
    SA_INT r = (x | y) & sa_hbit;
    return r == 0;
}

#endif //HACKERS_DELIGHT_SAI_MISC_H
