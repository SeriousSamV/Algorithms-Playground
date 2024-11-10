//
// Created by Samuel Vishesh Paul on 11/11/24.
//

#ifndef FLOATING_POINTER_UTILS_H
#define FLOATING_POINTER_UTILS_H
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
#include <sys/types.h>

long double *range(
    long double start,
    long double end,
    long double step,
    size_t *out_size);

bool is_equal_floating_point(
    long double expected,
    long double actual,
    int precision_epsilon);

#endif //FLOATING_POINTER_UTILS_H
