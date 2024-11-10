//
// Created by Samuel Vishesh Paul on 11/11/24.
//

#include <floating_pointer_utils.h>
#include <tgmath.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
#include <stdlib.h>

long double *range(
    const long double start,
    const long double end,
    const long double step,
    size_t *out_size) {
    const size_t cnt = (size_t) (end - start);
    long double *res = calloc(cnt, sizeof(long double));
    for (size_t i = 0; i < cnt; i++) {
        res[i] = start + (long double) i * step;
        *out_size = cnt;
    }
    return res;
}

bool is_equal_floating_point(
    const long double expected,
    const long double actual,
    const int precision_epsilon) {
    const long double diff = expected - actual;
    const long double epsilon = (long double) 1.f / powl(10.f, precision_epsilon);
    return diff < epsilon && diff > -epsilon;
}
