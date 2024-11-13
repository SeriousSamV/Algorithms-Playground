#include <assert.h>
#include <stdlib.h>
#include <big_decimal.h>
#include <string.h>

void test_lloa() {
    size_t num1_len = 0;
    size_t num1_buff_sz = 0;
    const char *num1 = lltoa(123, &num1_buff_sz, &num1_len);
    assert(strcmp(num1, "123") == 0);
    assert(num1_len == strlen(num1));
    assert(num1_buff_sz == 32);
}

void test_big_decimal_new() {
    big_decimal_t *big_decimal = big_decimal_new(10, 4);
    free(big_decimal);
}

int main() {
    test_lloa();
    test_big_decimal_new();
    return EXIT_SUCCESS;
}
