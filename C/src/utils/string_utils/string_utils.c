#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>
#include <string.h>

void reverse_string(char *const str, const size_t size) {
    if (str == NULL) return;
    const size_t len = strnlen(str, size);
    if (len <= 0) return;
    for (size_t i = 0; i < len / 2; i++) {
        const char temp = str[len - 1 - i];
        str[len - 1 - i] = str[i];
        str[i] = temp;
    }
}

char *lltoa(long long value, size_t *const restrict out_capacity, size_t *const restrict out_len) {
    char *buff = calloc(STRING_UTILS_MIN_CAPACITY, sizeof(char));
    *out_capacity = STRING_UTILS_MIN_CAPACITY;
    *out_len = 0;
    if (buff == NULL) {
        return nullptr;
    }
    char *p = buff;
    if (value < 0) {
        value = -value;
        *p++ = '-';
        (*out_len)++;
    }
    do {
        if (*out_capacity < *out_len + 1) {
            *out_capacity *= 2;
            buff = realloc(buff, *out_capacity);
            if (buff == nullptr) {
                return nullptr;
            }
        }
        *p++ = "0123456789"[value % 10];
        value /= 10;
        (*out_len)++;
    } while (value != 0);
    reverse_string(buff, *out_len + 1);
    return buff;
}

char *ulltoa(unsigned long long value, size_t *out_capacity, size_t *out_len) {
    char *buff = calloc(STRING_UTILS_MIN_CAPACITY, sizeof(char));
    size_t capacity = STRING_UTILS_MIN_CAPACITY;
    size_t len = 0;
    if (buff == NULL) {
        return nullptr;
    }
    char *p = buff;
    do {
        if (capacity < len + 1) {
            capacity *= 2;
            buff = realloc(buff, capacity);
            if (buff == nullptr) {
                return nullptr;
            }
        }
        *p++ = "0123456789"[value % 10];
        value /= 10;
        len++;
    } while (value != 0);
    reverse_string(buff, len + 1);
    if (out_capacity != NULL) *out_capacity = capacity;
    if (out_len != NULL) *out_len = len;
    return buff;
}

unsigned long long ull_from_digits_pow(int const base, const size_t pow) {
    if (pow == 0) {
        return 0;
    }
    unsigned long long result = 1;
    for (size_t i = 1; i < pow; i++) {
        result *= base;
    }
    return result;
}

unsigned long long ull_from_digits(const char *number, const size_t len) {
    if (len <= 0) return 0ll;
    unsigned long long res = 0ll;
    for (ssize_t i = len - 1; // NOLINT(*-narrowing-conversions)
         i >= 0;
         i--) {
        res += (number[i] - '0') * ull_from_digits_pow(10, len - i);
    }
    return res;
}

size_t ull_digits_count(unsigned long long number) {
    if (number == 0) {
        return 1;
    }
    size_t count = 0;
    while (number != 0) {
        number = number / 10;
        count++;
    }
    return count;
}
