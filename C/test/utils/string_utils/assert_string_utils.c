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

int main() {
    test_lltoa();
    return EXIT_SUCCESS;
}
