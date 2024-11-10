#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <simple_linear_regression.h>

void test_1() {
    long double alpha = 0;
    long double beta = 0;
    const long double x1[] = {1, 9, 1, 9, 1, 9};
    const long double y1[] = {1, 9, 1, 9, 1, 9};
    least_square_fit(x1, y1, 6, &alpha, &beta);
    printf("alpha = %Lf\n", alpha);
    printf("beta = %Lf\n", beta);
    assert(alpha > -0.001f && alpha < 0.001f);
    assert(beta - 1 > -0.001f && beta - 1 < 0.001f);
}

void test_2() {
    long double alpha = 0;
    long double beta = 0;
    size_t test_sz = 0;
    long double *x1 = range(-100.f, 100.f, 10.f, &test_sz);
    long double *y1 = calloc(test_sz, sizeof(long double));
    const long double ALPHA = -5.f;
    const long double BETA = 3.f;
    for (size_t i = 0; i < test_sz; i++) {
        y1[i] = BETA * x1[i] + ALPHA;
    }
    least_square_fit(x1, y1, test_sz, &alpha, &beta);
    free(x1);
    free(y1);
    printf("alpha = %Lf\n", alpha);
    printf("beta = %Lf\n", beta);
    assert(alpha - ALPHA > -0.01 && alpha - ALPHA < 0.01);
    assert(beta - BETA > -0.01 && beta - BETA < 0.01);
}

int main() {
    test_1();
    test_2();

    return EXIT_SUCCESS;
}
