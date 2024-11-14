// ReSharper disable CppVariableCanBeMadeConstexpr
#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
#include <stdio.h>
#include <string.h>

char *lltoa(long long value, size_t *out_capacity, size_t *out_len);

void test_lltoa() {
    size_t num1_len = 0;
    size_t num1_buff_sz = 0;
    const char *num1 = lltoa(123, &num1_buff_sz, &num1_len);
    assert(strcmp(num1, "123") == 0);
    assert(num1_len == strlen(num1));
    assert(num1_buff_sz == MIN_CAPACITY);
}

void test_big_decimal_new() {
    big_decimal_t *big_decimal = big_decimal_new(10, 4);
    assert(big_decimal != NULL);
    assert(strcmp(big_decimal->decimal_string, "4") == 0);
    assert(big_decimal->decimal_string_capacity == MIN_CAPACITY);
    assert(big_decimal->decimal_string_length == 1);
    assert(strcmp(big_decimal->number_string, "10") == 0);
    assert(big_decimal->number_string_capacity == MIN_CAPACITY);
    assert(big_decimal->number_string_length == 2);
    free(big_decimal);
}

char *add_number_strings(
    const char *restrict const a,
    const size_t a_len,
    const bool is_a_negative,
    const char *restrict const b,
    const size_t b_len,
    const bool is_b_negative,
    size_t *const restrict out_len,
    bool *const restrict out_is_negative);

void test_big_decimal_add() {
    const char a[] = "12";
    const char b[] = "24";
    size_t len = 0;
    bool is_negative = false;
    const char *res = add_number_strings(a, 2, false, b, 2, false, &len, &is_negative);
    printf("val=%s\n", res);
    assert(strcmp(res, "36") == 0);

    const char a1[] = "99";
    const char b1[] = "1";
    size_t len1 = 0;
    bool is_negative1 = false;
    const char *res1 = add_number_strings(a1, 2, false, b1, 1, false, &len1, &is_negative1);
    printf("val=%s\n", res1);
    assert(strcmp(res1, "100") == 0);

    const char a2[] = "101";
    const char b2[] = "1";
    size_t len2 = 0;
    bool is_negative2 = false;
    const char *res2 = add_number_strings(a2, 3, false, b2, 1, false, &len2, &is_negative2);
    printf("val=%s\n", res2);
    assert(strcmp(res2, "102") == 0);
}

int main() {
    test_lltoa();
    test_big_decimal_new();
    test_big_decimal_add();
    return EXIT_SUCCESS;
}
