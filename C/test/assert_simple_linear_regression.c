#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <simple_linear_regression.h>

bool is_equal_floating_point(
    const long double expected,
    const long double actual,
    const int precision_epsilon) {
    const long double diff = expected - actual;
    const long double epsilon = (long double) 1.f / powl(10.f, precision_epsilon);
    return diff < epsilon && diff > -epsilon;
}

void test_1() {
    const long double x[] = {1, 9, 1, 9, 1, 9};
    const long double y[] = {1, 9, 1, 9, 1, 9};
    long double alpha = 0;
    long double beta = 0;
    // ReSharper disable CppVariableCanBeMadeConstexpr
    const long double ALPHA = 0;
    const long double BETA = 1;
    // ReSharper restore CppVariableCanBeMadeConstexpr
    least_square_fit(x, y, 6, &alpha, &beta);
    assert(is_equal_floating_point(alpha, ALPHA, 5));
    assert(is_equal_floating_point(beta, BETA, 5));
}

void test_2() {
    size_t test_sz = 0;
    long double *x = range(-100.f, 100.f, 10.f, &test_sz);
    long double *y = calloc(test_sz, sizeof(long double));
    long double alpha = 0;
    long double beta = 0;
    // ReSharper disable CppVariableCanBeMadeConstexpr
    const long double ALPHA = -5.f;
    const long double BETA = 3.f;
    // ReSharper restore CppVariableCanBeMadeConstexpr
    for (size_t i = 0; i < test_sz; i++) {
        y[i] = BETA * x[i] + ALPHA;
    }
    least_square_fit(x, y, test_sz, &alpha, &beta);
    free(x);
    free(y);
    assert(is_equal_floating_point(alpha, ALPHA, 2));
    assert(!is_equal_floating_point(alpha, ALPHA, 3)); // The accuracy is very low...
    assert(is_equal_floating_point(beta, BETA, 2));
}

int main() {
    test_1();
    test_2();

    return EXIT_SUCCESS;
}
