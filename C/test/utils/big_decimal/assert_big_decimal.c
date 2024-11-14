#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
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

int main() {
    test_lltoa();
    test_big_decimal_new();
    return EXIT_SUCCESS;
}
