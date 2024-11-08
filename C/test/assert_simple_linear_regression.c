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

    if (!(alpha == 0 || alpha == 1))
        alpha = alpha * 100 / 100;
    char *alpha_str = malloc(10 * sizeof(char));
    snprintf(alpha_str, 10, "%.2Lf", alpha);
    printf("alpha_str = %s\n", alpha_str);
    assert(strcmp(alpha_str, "0.00") == 0);
    free(alpha_str);

    if (!(beta == 0 || beta == 1))
        beta = (beta * 100) / 100;
    char *beta_str = malloc(10 * sizeof(char));
    snprintf(beta_str, 10, "%.2Lf", beta);
    printf("beta_str = %s\n", beta_str);
    assert(strcmp(beta_str, "1.00") == 0);
    free(beta_str);
}

void test_2() {
    long double alpha = 0;
    long double beta = 0;
    size_t test_sz = 0;
    long double *x1 = range(-100.f, 100.f, 10.f, &test_sz);
    long double *y1 = calloc(test_sz, sizeof(long double));
    for (size_t i = 0; i < test_sz; i++) {
        y1[i] = 3 * x1[i] - 5;
    }
    least_square_fit(x1, y1, test_sz, &alpha, &beta);
    free(x1);
    free(y1);
    printf("alpha = %Lf\n", alpha);
    printf("beta = %Lf\n", beta);

    if (!(alpha == 0 || alpha == 1))
        alpha = (long double) ((long int) alpha * 100) / 100.f;
    char *alpha_str = malloc(10 * sizeof(char));
    snprintf(alpha_str, 10, "%.2Lf", alpha);
    printf("alpha_str = %s\n", alpha_str);
    assert(strcmp(alpha_str, "-5.00") == 0);
    free(alpha_str);

    if (!(beta == 0 || beta == 1))
        beta = (long double) ((long int) beta * 100) / 100.f;
    char *beta_str = malloc(10 * sizeof(char));
    snprintf(beta_str, 10, "%.2Lf", beta);
    printf("beta_str = %s\n", beta_str);
    assert(strcmp(beta_str, "3.00") == 0);
    free(beta_str);
}

int main() {
    test_1();
    test_2();

    return EXIT_SUCCESS;
}
