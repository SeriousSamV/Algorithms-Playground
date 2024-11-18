// ReSharper disable CppVariableCanBeMadeConstexpr
#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
#include <stdio.h>
#include <string.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>

#include "string_utils.h"
// ReSharper restore CppUnusedIncludeDirective

void test_big_decimal_new() {
    big_decimal_t *big_decimal = big_decimal_new(10, 4);
    assert(big_decimal != NULL);
    assert(strcmp(big_decimal->decimal_string, "4") == 0);
    assert(big_decimal->decimal_string_capacity == STRING_UTILS_MIN_CAPACITY);
    assert(big_decimal->decimal_string_length == 1);
    assert(strcmp(big_decimal->number_string, "10") == 0);
    assert(big_decimal->number_string_capacity == STRING_UTILS_MIN_CAPACITY);
    assert(big_decimal->number_string_length == 2);
    free(big_decimal);
}

// void test_sign_of_result() {
//     const char a1[] = "111";
//     const char b1[] = "1";
//     bool is_negative_1 = false;
//     size_t len1 = 0;
//     char *res1 = add_number_strings(a1, 3, true, b1, 1, false, &len1, &is_negative_1);
//     assert(is_negative_1 == true);
//     free(res1);
//     res1 = add_number_strings(a1, 3, false, b1, 1, true, &len1, &is_negative_1);
//     assert(is_negative_1 == false);
//     free(res1);
//     res1 = add_number_strings(a1, 3, true, b1, 1, true, &len1, &is_negative_1);
//     assert(is_negative_1 == true);
//     free(res1);
//     res1 = add_number_strings(a1, 3, false, b1, 1, false, &len1, &is_negative_1);
//     assert(is_negative_1 == false);
//     free(res1);
//
//     const char a2[] = "111";
//     const char b2[] = "110";
//     bool is_negative_2 = false;
//     size_t len2 = 0;
//     char *res2 = add_number_strings(a2, 3, true, b2, 3, false, &len2, &is_negative_2);
//     assert(is_negative_2 == true);
//     free(res2);
//     res2 = add_number_strings(a2, 3, false, b2, 3, true, &len2, &is_negative_2);
//     assert(is_negative_2 == false);
//     free(res2);
//     res2 = add_number_strings(a2, 3, true, b2, 3, true, &len2, &is_negative_2);
//     assert(is_negative_2 == true);
//     free(res2);
//     res2 = add_number_strings(a2, 3, false, b2, 3, false, &len2, &is_negative_2);
//     assert(is_negative_2 == false);
//     free(res2);
//
//     const char a3[] = "1";
//     const char b3[] = "111";
//     bool is_negative_3 = false;
//     size_t len3 = 0;
//     char *res3 = add_number_strings(a3, 1, true, b3, 3, false, &len3, &is_negative_3);
//     assert(is_negative_3 == false);
//     free(res3);
//     res3 = add_number_strings(a3, 1, false, b3, 3, true, &len3, &is_negative_3);
//     assert(is_negative_3 == true);
//     free(res3);
//     res3 = add_number_strings(a3, 1, true, b3, 3, true, &len3, &is_negative_3);
//     assert(is_negative_3 == true);
//     free(res3);
//     res3 = add_number_strings(a3, 1, false, b3, 3, false, &len3, &is_negative_3);
//     assert(is_negative_3 == false);
//     free(res3);
// }

int main() {
    test_big_decimal_new();
    return EXIT_SUCCESS;
}
