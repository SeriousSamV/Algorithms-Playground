//
// Created by Samuel Vishesh Paul on 11/11/24.
//

#ifndef SIMPLE_LINEAR_REGRESSION_V2_H
#define SIMPLE_LINEAR_REGRESSION_V2_H

#include <sys/types.h>

void least_square_fit_v2(
    const long double *x,
    const long double *y,
    size_t size,
    long double *out_alpha,
    long double *out_beta);

#endif //SIMPLE_LINEAR_REGRESSION_V2_H
