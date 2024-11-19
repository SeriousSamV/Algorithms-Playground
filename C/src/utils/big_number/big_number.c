#include <big_number.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <nullptr_fix.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

#include "string_utils.h"

big_number_t *big_number_sub_internal(
    const big_number_t *restrict bn_a,
    const big_number_t *restrict bn_b);

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

/**
 * Adds two `big_number_t`
 *
 * @param bn_a The first big number input.
 * @param bn_b The second big number input.
 * @return A new big_number_t structure containing the sum of bn_a and bn_b.
 */
big_number_t *big_number_add(
    const big_number_t *restrict const bn_a,
    const big_number_t *restrict const bn_b) {
    const size_t a_len = bn_a->length;
    const bool is_a_negative = bn_a->is_negative;
    const size_t b_len = bn_b->length;
    const bool is_b_negative = bn_b->is_negative;
    errno = 0;
    if ((is_a_negative && is_b_negative) || (!is_a_negative && !is_b_negative)) {
        big_number_t * result = big_number_add_internal(bn_a, bn_b);
        result->is_negative = is_a_negative;
        return result;
    }
    bool is_mod_a_bigger = false;
    bool out_is_negative = false;
    if (a_len > b_len) {
        out_is_negative = is_a_negative;
        is_mod_a_bigger = true;
    } else if (b_len > a_len) {
        out_is_negative = is_b_negative;
        is_mod_a_bigger = false;
    } else {
        const char *a = bn_a->number;
        const char *b = bn_b->number;
        for (size_t i = 0; i < a_len; i++) {
            if (a[i] > b[i]) {
                out_is_negative = is_a_negative;
                is_mod_a_bigger = true;
                break;
            }
            if (b[i] > a[i]) {
                out_is_negative = is_b_negative;
                is_mod_a_bigger = false;
                break;
            }
        }
    }
    const big_number_t ac = {
        .capacity = bn_a->capacity, .number = bn_a->number, .is_negative = false, .length = bn_a->length
    };
    const big_number_t bc = {
        .capacity = bn_b->capacity, .number = bn_b->number, .is_negative = false, .length = bn_b->length
    };
    if (is_mod_a_bigger) {
        big_number_t *result = big_number_sub_internal(&ac, &bc);
        result->is_negative = out_is_negative;
        return result;
    }
    big_number_t *result = big_number_sub_internal(&bc, &ac);
    result->is_negative = out_is_negative;
    return result;
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
    for (size_t i = 0; i < bn_b->length; i++) {
        const unsigned int va = (unsigned int) *pa - '0';
        const unsigned int vb = (unsigned int) *pb - '0';
        if (va < vb) {
            size_t bt = 1;
            for (; *(pa - bt) == '0' && *(pa - bt) != '\0'; bt++) {
                *(pa - bt) = '9';
            }
            *(pa - bt) = *(pa - bt) - 1; // NOLINT(*-narrowing-conversions)
            *pr++ = 10 + va - vb + '0'; // NOLINT(*-narrowing-conversions)
        } else {
            *pr++ = va - vb + '0'; // NOLINT(*-narrowing-conversions)
        }
        pa--;
        pb--;
    }
    while (pa >= a) {
        *pr++ = *pa;
        pa--;
    }
    pr--;
    while (*pr == '0' && pr > r) {
        *pr = '\0';
        pr--;
    }
    reverse_string(r, r_cap);
    big_number_t *result = big_number_from_str(r, r_cap);
    free(r);
    free(b);
    free(a);
    return result;
}

big_number_t *big_number_sub(const big_number_t *bn_a, const big_number_t *bn_b) {
}
