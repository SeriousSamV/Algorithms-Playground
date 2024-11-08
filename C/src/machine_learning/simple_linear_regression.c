//
// Created by Samuel Vishesh Paul on 09/11/24.
//

#include <math.h>
#include <simple_linear_regression.h>
#include <nullptr_fix.h>
#include <stdlib.h>


long double mean(const long double *x, const size_t n) {
    long double sum = 0;
    for (size_t i = 0; i < n; i++) { sum += x[i]; }
    return sum / (long double) n;
}

long double dot(const long double *x, const long double *y, const size_t n) {
    if (x == nullptr || y == nullptr) return 0;
    long double sum = 0;
    // ReSharper disable CppDFANullDereference
    for (size_t i = 0; i < n; i++) { sum += x[i] * y[i]; }
    // ReSharper restore CppDFANullDereference
    return sum;
}

long double *deviation_from(const long double *x, const long double from_val, const size_t n) {
    long double *deviation = calloc(n, sizeof(long double));
    for (size_t i = 0; i < n; i++) { deviation[i] = x[i] - from_val; }
    return deviation;
}

long double sum_of_squares(const long double *x, const size_t n) {
    return dot(x, x, n);
}

long double variance(const long double *x, const size_t n) {
    if (x == nullptr) return 0;
    long double *deviation = deviation_from(x, mean(x, n), n);
    const long double res = sum_of_squares(deviation, n) / (long double) n - 1;
    free(deviation);
    return res;
}

long double standard_deviation(const long double *x, const size_t n) {
    return sqrtl(variance(x, n));
}

long double covariance(const long double *x, const long double *y, const size_t n) {
    const long double mean_x = mean(x, n);
    const long double mean_y = mean(y, n);
    long double *de_mean_x = deviation_from(x, mean_x, n);
    long double *de_mean_y = deviation_from(y, mean_y, n);
    const long double res = dot(de_mean_x, de_mean_y, n) / (long double) n - 1;
    free(de_mean_x);
    free(de_mean_y);
    return res;
}

long double correlation(const long double *x, const long double *y, const size_t n) {
    const long double stddev_x = standard_deviation(x, n);
    const long double stddev_y = standard_deviation(y, n);
    if (stddev_x > 0 && stddev_y > 0) {
        return covariance(x, y, n) / stddev_x / stddev_y;
    }
    return 0;
}

long double predict(const long double alpha, const long double beta, const long double x_i) {
    return beta * x_i + alpha;
}

long double error(const long double alpha, const long double beta, const long double x_i, const long double y_i) {
    return predict(alpha, beta, x_i) - y_i;
}

long double sum(const long double *x, const size_t size) {
    long double sum = 0;
    for (size_t i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum;
}

long double sum_of_squared_errors(
    const long double alpha,
    const long double beta,
    const long double *x,
    const long double *y,
    const size_t size) {
    long double res = 0;
    for (size_t i = 0; i < size; i++) {
        res += powl(error(alpha, beta, x[i], y[i]), 2);
    }
    return res;
}

void least_square_fit(
    const long double *x,
    const long double *y,
    const size_t size,
    long double *out_alpha,
    long double *out_beta) {
    *out_beta = correlation(x, y, size) * standard_deviation(y, size) / standard_deviation(x, size);
    *out_alpha = mean(y, size) - (*out_beta * mean(x, size));
}

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
