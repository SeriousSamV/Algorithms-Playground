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

big_number_t *big_number_new(void);

big_number_t *big_number_from_str(const char *number, size_t capacity);

big_number_t *big_number_from_ll(long long number);

big_number_t *big_number_from_ull(unsigned long long number);

big_number_t *big_number_add(
    const big_number_t *restrict bn_a,
    const big_number_t *restrict bn_b);

big_number_t *big_number_sub(
    const big_number_t *restrict bn_a,
    const big_number_t *restrict bn_b);

void big_number_free(big_number_t *bn);

#endif //BIG_NUMBER_H
