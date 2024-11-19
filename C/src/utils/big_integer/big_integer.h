#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
#include <sys/types.h>

#ifndef BIG_INTEGER_DEFAULT_BUFF_SIZE
#define BIG_INTEGER_DEFAULT_BUFF_SIZE 64
#endif

#ifndef BIG_INTEGER_MAX_DIGITS
#define BIG_INTEGER_MAX_DIGITS 1024
#endif

typedef struct big_integer {
    char *number;
    size_t length;
    size_t capacity;
    bool is_negative;
} big_integer_t;

big_integer_t *big_integer_new(void);

big_integer_t *big_integer_from_str(const char *number, size_t capacity);

big_integer_t *big_integer_from_ll(long long number);

big_integer_t *big_integer_from_ull(unsigned long long number);

big_integer_t *big_integer_add(
    const big_integer_t *restrict bi_a,
    const big_integer_t *restrict bi_b);

big_integer_t *big_integer_sub(
    const big_integer_t *restrict bi_a,
    const big_integer_t *restrict bi_b);

void big_integer_free(big_integer_t *bi);

#endif //BIG_INTEGER_H
