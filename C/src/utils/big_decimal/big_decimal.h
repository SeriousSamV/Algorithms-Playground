#ifndef BIG_DECIMAL_H
#define BIG_DECIMAL_H
#include <sys/types.h>

typedef struct big_decimal {
    char *number_string;
    size_t number_string_length;
    size_t number_string_capacity;
    char *decimal_string;
    size_t decimal_string_length;
    size_t decimal_string_capacity;
    bool is_negative;
} big_decimal_t;

big_decimal_t *big_decimal_new(long long number, long long decimal);

big_decimal_t *big_decimal_from_str(const char *number_str, size_t number_str_len);

void big_decimal_free(big_decimal_t *bd);

#endif //BIG_DECIMAL_H
