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
    *out_capacity = STRING_UTILS_MIN_CAPACITY;
    *out_len = 0;
    if (buff == NULL) {
        return nullptr;
    }
    char *p = buff;
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

long long from_digits(const char *number, const size_t len) {
    char *t = calloc(len + 1, sizeof(char));
    for (size_t i = 0; i < len; i++) {
        t[i] = number[i];
    }
    t[len] = '\0';
    const long long res = strtoll(t, nullptr, 10);
    free(t);
    return res;
}
