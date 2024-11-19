// ReSharper disable CppVariableCanBeMadeConstexpr
#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
#include <stdio.h>
#include <string.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

#include <string_utils.h>

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

int main() {
    test_big_decimal_new();
    return EXIT_SUCCESS;
}
