#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <floating_pointer_utils.h>
#include <simple_linear_regression_v2.h>

void test_1() {
    const long double x[] = {1, 9, 1, 9, 1, 9};
    const long double y[] = {1, 9, 1, 9, 1, 9};
    long double alpha = 0;
    long double beta = 0;
    // ReSharper disable CppVariableCanBeMadeConstexpr
    const long double ALPHA = 0;
    const long double BETA = 1;
    // ReSharper restore CppVariableCanBeMadeConstexpr
    least_square_fit_v2(x, y, 6, &alpha, &beta);
    printf("test_1: alpha=%Lf\t beta=%Lf\n", alpha, beta);
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
    least_square_fit_v2(x, y, test_sz, &alpha, &beta);
    free(x);
    free(y);
    printf("test_2: alpha=%Lf\t beta=%Lf\n", alpha, beta);
    assert(is_equal_floating_point(alpha, ALPHA, 5)); // accuracy is high compared to v1
    assert(is_equal_floating_point(beta, BETA, 5));
}

void test_3() {
    const long double x[] = {1, 2, 3, 4, 5};
    const long double y[] = {3, 4, 5, 6, 7};
    long double alpha = 0;
    long double beta = 0;
    least_square_fit_v2(x, y, 5, &alpha, &beta);
    printf("test_3: alpha=%Lf\t beta=%Lf\n", alpha, beta);
    assert(is_equal_floating_point(alpha, 2, 2));
    assert(is_equal_floating_point(beta, 1, 2));
}

int main() {
    test_1();
    test_2();
    test_3();

    return EXIT_SUCCESS;
}
