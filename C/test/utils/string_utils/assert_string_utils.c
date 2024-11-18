// ReSharper disable CppVariableCanBeMadeConstexpr
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <string_utils.h>

void test_lltoa() {
    size_t num1_len = 0;
    size_t num1_buff_sz = 0;
    const char *num1 = lltoa(123, &num1_buff_sz, &num1_len);
    assert(strcmp(num1, "123") == 0);
    assert(num1_len == strlen(num1));
    assert(num1_buff_sz == STRING_UTILS_MIN_CAPACITY);
}

void test_from_digits() {
    const char input[] = "98765432100";
    assert(ull_from_digits(input, 4) == 9876);
    assert(ull_from_digits(input, 8) == 98765432);
    assert(ull_from_digits(input + 2, 4) == 7654);
    assert(ull_from_digits("4", 1) == 4);
}

int main() {
    test_lltoa();
    test_from_digits();
    return EXIT_SUCCESS;
}
