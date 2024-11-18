#include <big_number.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <nullptr_fix.h>

#include "string_utils.h"

big_number_t *big_number_new(void) {
    big_number_t *bn = malloc(sizeof(big_number_t));
    if (bn == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for big_number_t");
        perror(error_msg);
        return nullptr;
    }
    bn->capacity = BIG_NUMBER_DEFAULT_BUFF_SIZE;
    bn->number = calloc(bn->capacity, sizeof(char));
    if (bn->number == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for number buffer");
        perror(error_msg);
        return nullptr;
    }
    bn->number[0] = '0';
    bn->number[1] = '\0';
    bn->length = 1;
    bn->is_negative = false;
    return bn;
}

big_number_t *big_number_from_str(const char *number, const size_t length) {
    big_number_t *bn = malloc(sizeof(big_number_t));
    if (bn == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for big_number_t");
        perror(error_msg);
        return nullptr;
    }
    const size_t capacity = length + 1;
    const char *num_ptr = number;
    if (number[0] == '-') {
        bn->is_negative = true;
        num_ptr++;
    } else {
        bn->is_negative = false;
    }
    bn->number = calloc(capacity, sizeof(char));
    if (bn->number == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for number buffer");
        perror(error_msg);
        return nullptr;
    }
    strncpy(bn->number, num_ptr, length);
    bn->length = strnlen(bn->number, BIG_NUMBER_MAX_DIGITS);
    bn->capacity = capacity;
    return bn;
}

big_number_t *big_number_from_ll(const long long number) {
    big_number_t *bn = big_number_new();
    bn->number = lltoa(number, &bn->capacity, &bn->length);
    if (number < 0) {
        bn->is_negative = true;
    }
    return bn;
}

big_number_t *big_number_from_ull(const unsigned long long number) {
    big_number_t *bn = big_number_new();
    bn->number = ulltoa(number, &bn->capacity, &bn->length);
    bn->is_negative = false;
    return bn;
}

void big_number_free(big_number_t *bn) {
    free(bn->number);
    free(bn);
}

big_number_t *add_number_strings_if_both_signs_equal(
    const big_number_t *restrict const bn_a,
    const big_number_t *restrict const bn_b) {
    const char *a = bn_a->number;
    const size_t a_len = bn_a->length;
    const bool is_a_negative = bn_a->is_negative;
    const char *b = bn_b->number;
    const size_t b_len = bn_b->length;
    const bool is_b_negative = bn_b->is_negative;

    big_number_t *result_bn = big_number_new();
    int carry = 0;
    char *result_ptr = result_bn->number;
    result_bn->is_negative = (bool) is_a_negative && is_b_negative;
    const char *pa = a + a_len - 1;
    const char *pb = b + b_len - 1;
    while (pa >= a && pb >= b) {
        const int va = *pa - '0';
        const int vb = *pb - '0';
        int r = va + vb + carry;
        if (r >= 10) {
            carry = r / 10 % 10;
            r = r % 10;
        } else {
            carry = 0;
        }
        *result_ptr++ = (char) (r + '0');
        pa--;
        pb--;
    }
    while (pa >= a) {
        const int va = *pa - '0';
        int r = va + carry;
        if (r >= 10) {
            carry = r / 10 % 10;
            r = r % 10;
        } else {
            carry = 0;
        }
        *result_ptr++ = (char) (r + '0');
        pa--;
    }
    while (pb >= b) {
        const int vb = *pb - '0';
        int r = vb + carry;
        if (r >= 10) {
            carry = r / 10 % 10;
            r = r % 10;
        } else {
            carry = 0;
        }
        *result_ptr++ = (char) (r + '0');
        pb--;
    }
    if (carry > 0) {
        *result_ptr = (char) (carry + '0');
    }
    reverse_string(result_bn->number, result_bn->capacity);
    return result_bn;
}

big_number_t *big_number_add(
    const big_number_t *restrict const bn_a,
    const big_number_t *restrict const bn_b) {
    const char *a = bn_a->number;
    const size_t a_len = bn_a->length;
    const bool is_a_negative = bn_a->is_negative;
    const char *b = bn_b->number;
    const size_t b_len = bn_b->length;
    const bool is_b_negative = bn_b->is_negative;
    errno = 0;
    if ((is_a_negative && is_b_negative) || (!is_a_negative && !is_b_negative)) {
        return add_number_strings_if_both_signs_equal(bn_a, bn_b);
    }
    bool out_is_negative = false;
    if (a_len > b_len) {
        out_is_negative = is_a_negative;
    } else if (b_len > a_len) {
        out_is_negative = is_b_negative;
    } else {
        for (size_t i = 0;; i++) {
            if (a[i] != '\0' && b[i] == '\0') {
                out_is_negative = is_a_negative;
                break;
            }
            if (b[i] != '\0' && a[i] == '\0') {
                out_is_negative = is_b_negative;
                break;
            }
            if (a[i] > b[i]) {
                out_is_negative = is_a_negative;
                break;
            }
            if (b[i] > a[i]) {
                out_is_negative = is_b_negative;
                break;
            }
        }
    }
    return nullptr;
}
