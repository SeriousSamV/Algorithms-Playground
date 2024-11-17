#include <big_number.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <nullptr_fix.h>

big_number_t * big_number_new(const char *number, const size_t length) {
    big_number_t *bn = malloc(sizeof(big_number_t));
    const size_t capacity = length + 1;
    const char *num_ptr = number;
    if (number[0] == '-') {
        bn->is_negative = true;
        num_ptr++;
    } else {
        bn->is_negative = false;
    }
    bn->number = calloc(capacity, sizeof(char));
    strncpy(bn->number, num_ptr, length);
    bn->length = strnlen(bn->number, BIG_NUMBER_MAX_DIGITS);
    bn->capacity = capacity;
    return bn;
}

big_number_t * big_number_from_ll(long long number) {
    big_number_t *bn = big_number_from_ull(number < 0 ? -number : number);
    if (number < 0) {
        bn->is_negative = true;
    }
    return bn;
}

big_number_t * big_number_from_ull(unsigned long long number) {
    big_number_t *bn = malloc(sizeof(big_number_t));
    bn->capacity = snprintf(nullptr, 0, "%lld", LLONG_MIN) + 1;
    bn->number = (char *) calloc(bn->capacity, sizeof(char));
    bn->length = snprintf(bn->number, bn->capacity, "%lld", number) + 1;
    bn->is_negative = false;

    return bn;
}

void big_number_free(big_number_t *bn) {
    free(bn->number);
    free(bn);
}
