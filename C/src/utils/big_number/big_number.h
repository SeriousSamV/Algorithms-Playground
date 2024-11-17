#ifndef BIG_NUMBER_H
#define BIG_NUMBER_H
#include <sys/types.h>

#ifndef BIG_NUMBER_DEFAULT_BUFF_SIZE
#define BIG_NUMBER_DEFAULT_BUFF_SIZE 64
#endif

#ifndef BIG_NUMBER_MAX_DIGITS
#define BIG_NUMBER_MAX_DIGITS 1024
#endif

typedef struct big_number {
    char *number;
    size_t length;
    size_t capacity;
    bool is_negative;
} big_number_t;

big_number_t *big_number_new(const char *number, size_t length);

big_number_t *big_number_from_ll(long long number);

big_number_t *big_number_from_ull(unsigned long long number);

void big_number_free(big_number_t *bn);

#endif //BIG_NUMBER_H
