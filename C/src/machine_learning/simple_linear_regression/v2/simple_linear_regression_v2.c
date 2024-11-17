//
// Created by Samuel Vishesh Paul on 11/11/24.
//

#include "simple_linear_regression_v2.h"

#include <tgmath.h>

void least_square_fit_v2(
    const long double *const x,
    const long double *const y,
    const size_t size,
    long double *out_alpha,
    long double *out_beta) {
    long double sum_x = 0;
    long double sum_y = 0;
    for (size_t i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
    }
    const long double mean_x = sum_x / (long double) size;
    const long double mean_y = sum_y / (long double) size;

    long double num = 0;
    long double den = 0;
    for (size_t i = 0; i < size; i++) {
        num += (x[i] - mean_x) * (y[i] - mean_y);
        den += pow(x[i] - mean_x, 2);
    }
    *out_beta = num / den;
    *out_alpha = mean_y - (*out_beta * mean_x);
}
