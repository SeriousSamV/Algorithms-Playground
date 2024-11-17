#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <stddef.h>

#ifndef STRING_UTILS_MIN_CAPACITY
#define STRING_UTILS_MIN_CAPACITY 16
#endif

void reverse_string(char *str, size_t size);

char *lltoa(long long value, size_t *out_capacity, size_t *out_len);

#endif