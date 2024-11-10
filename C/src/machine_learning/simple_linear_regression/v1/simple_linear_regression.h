#ifndef SIMPLE_LINEAR_REGRESSION_H
#define SIMPLE_LINEAR_REGRESSION_H
#include <sys/types.h>

void least_square_fit(
    const long double *x,
    const long double *y,
    size_t size,
    long double *out_alpha,
    long double *out_beta);

long double *range(
    long double start,
    long double end,
    long double step,
    size_t *out_size);

#endif //SIMPLE_LINEAR_REGRESSION_H
