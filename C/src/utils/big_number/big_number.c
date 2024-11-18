#include <big_number.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
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

big_number_t *big_number_from_str(const char *number, const size_t capacity) {
    if (number == NULL || capacity == 0) {
        return nullptr;
    }
    big_number_t *bn = malloc(sizeof(big_number_t));
    if (bn == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for big_number_t");
        perror(error_msg);
        return nullptr;
    }
    const size_t final_capacity = capacity + 1;
    if (number[0] == '-') {
        bn->is_negative = true;
        number++;
    } else {
        bn->is_negative = false;
    }
    bn->number = calloc(final_capacity, sizeof(char));
    if (bn->number == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for number buffer");
        perror(error_msg);
        return nullptr;
    }
    strncpy(bn->number, number, capacity);
    bn->length = strnlen(bn->number, BIG_NUMBER_MAX_DIGITS);
    bn->capacity = final_capacity;
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

big_number_t *big_number_add_internal(
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
        return big_number_add_internal(bn_a, bn_b);
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

/**
 *
 * @param bn_a a where a > b && a > 0
 * @param bn_b b where b < a && b > 0
 * @return val
 */
big_number_t *big_number_sub_internal(
    const big_number_t *restrict const bn_a,
    const big_number_t *restrict const bn_b) {
    char *const a = strndup(bn_a->number, bn_a->length + 1);
    char *pa = a + bn_a->length - 1;
    char *const b = strndup(bn_b->number, bn_b->length + 1);
    const char *pb = b + bn_b->length - 1;
    const size_t r_cap = bn_a->capacity + 1;
    char *const r = calloc(r_cap, sizeof(char));
    char *pr = r;
    size_t a_len = bn_a->length;
    for (size_t i = 0; i < bn_b->length; i++) {
        const unsigned int va = (unsigned int) *pa - '0';
        const unsigned int vb = (unsigned int) *pb - '0';
        if (va < vb) {
            size_t borrow_tracker = 1;
            for (; *(pa - borrow_tracker) == '0' && *(pa - borrow_tracker) != '\0'; borrow_tracker++) {
                *(pa - borrow_tracker) = '9';
            }
            *(pa - borrow_tracker) = *(pa - borrow_tracker) - 1; // NOLINT(*-narrowing-conversions)
            *pr++ = 10 + va - vb + '0'; // NOLINT(*-narrowing-conversions)
            a_len--;
        } else {
            *pr++ = va - vb + '0'; // NOLINT(*-narrowing-conversions)
        }
        pa--;
        pb--;
    }
    for (ssize_t i = a_len - bn_b->length; // NOLINT(*-narrowing-conversions)
         i > 0;
         i--) {
        *pr++ = *pa;
        pa--;
    }
    big_number_t *result = big_number_from_str(r, r_cap);
    free(r);
    free(b);
    free(a);
    return result;
}

big_number_t *big_number_sub(const big_number_t *bn_a, const big_number_t *bn_b) {
}
