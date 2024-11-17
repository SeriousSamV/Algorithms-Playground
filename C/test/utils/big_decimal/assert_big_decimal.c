// ReSharper disable CppVariableCanBeMadeConstexpr
#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
#include <stdio.h>
#include <string.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

char *lltoa(long long value, size_t *out_capacity, size_t *out_len);

char *add_number_strings(
    const char *restrict a,
    size_t a_len,
    bool is_a_negative,
    const char *restrict b,
    size_t b_len,
    bool is_b_negative,
    size_t *restrict out_len,
    bool *restrict out_is_negative);

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

void test_big_decimal_add() {
    const char a[] = "12";
    const char b[] = "24";
    size_t len = 0;
    bool is_negative = false;
    const char *res = add_number_strings(a, 2, false, b, 2, false, &len, &is_negative);
    printf("val=%s\n", res);
    assert(strcmp(res, "36") == 0);
    assert(is_negative == false);

    const char a1[] = "99";
    const char b1[] = "1";
    size_t len1 = 0;
    bool is_negative1 = false;
    const char *res1 = add_number_strings(a1, 2, false, b1, 1, false, &len1, &is_negative1);
    printf("val=%s\n", res1);
    assert(strcmp(res1, "100") == 0);
    assert(is_negative1 == false);

    const char a2[] = "101";
    const char b2[] = "1";
    size_t len2 = 0;
    bool is_negative2 = false;
    const char *res2 = add_number_strings(a2, 3, false, b2, 1, false, &len2, &is_negative2);
    printf("val=%s\n", res2);
    assert(strcmp(res2, "102") == 0);
    assert(is_negative2 == false);

    const char a3[] = "101";
    const char b3[] = "1";
    size_t len3 = 0;
    bool is_negative3 = false;
    const char *res3 = add_number_strings(a3, 3, true, b3, 1, true, &len3, &is_negative3);
    printf("val=%s\n", res2);
    assert(strcmp(res3, "102") == 0);
    assert(is_negative3 == true);
}

void test_sign_of_result() {
    const char a1[] = "111";
    const char b1[] = "1";
    bool is_negative_1 = false;
    size_t len1 = 0;
    char *res1 = add_number_strings(a1, 3, true, b1, 1, false, &len1, &is_negative_1);
    assert(is_negative_1 == true);
    free(res1);
    res1 = add_number_strings(a1, 3, false, b1, 1, true, &len1, &is_negative_1);
    assert(is_negative_1 == false);
    free(res1);
    res1 = add_number_strings(a1, 3, true, b1, 1, true, &len1, &is_negative_1);
    assert(is_negative_1 == true);
    free(res1);
    res1 = add_number_strings(a1, 3, false, b1, 1, false, &len1, &is_negative_1);
    assert(is_negative_1 == false);
    free(res1);

    const char a2[] = "111";
    const char b2[] = "110";
    bool is_negative_2 = false;
    size_t len2 = 0;
    char *res2 = add_number_strings(a2, 3, true, b2, 3, false, &len2, &is_negative_2);
    assert(is_negative_2 == true);
    free(res2);
    res2 = add_number_strings(a2, 3, false, b2, 3, true, &len2, &is_negative_2);
    assert(is_negative_2 == false);
    free(res2);
    res2 = add_number_strings(a2, 3, true, b2, 3, true, &len2, &is_negative_2);
    assert(is_negative_2 == true);
    free(res2);
    res2 = add_number_strings(a2, 3, false, b2, 3, false, &len2, &is_negative_2);
    assert(is_negative_2 == false);
    free(res2);

    const char a3[] = "1";
    const char b3[] = "111";
    bool is_negative_3 = false;
    size_t len3 = 0;
    char *res3 = add_number_strings(a3, 1, true, b3, 3, false, &len3, &is_negative_3);
    assert(is_negative_3 == false);
    free(res3);
    res3 = add_number_strings(a3, 1, false, b3, 3, true, &len3, &is_negative_3);
    assert(is_negative_3 == true);
    free(res3);
    res3 = add_number_strings(a3, 1, true, b3, 3, true, &len3, &is_negative_3);
    assert(is_negative_3 == true);
    free(res3);
    res3 = add_number_strings(a3, 1, false, b3, 3, false, &len3, &is_negative_3);
    assert(is_negative_3 == false);
    free(res3);
}

int main() {
    test_lltoa();
    test_big_decimal_new();
    test_big_decimal_add();
    test_sign_of_result();
    return EXIT_SUCCESS;
}
