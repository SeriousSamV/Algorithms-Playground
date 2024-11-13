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
    bool is_positive;
} big_decimal_t;

big_decimal_t *big_decimal_new(const long long number, const long long decimal);

#endif //BIG_DECIMAL_H