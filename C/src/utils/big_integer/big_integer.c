#include <big_integer.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <nullptr_fix.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

#include "string_utils.h"

big_integer_t *big_integer_sub_internal(
    const big_integer_t *restrict bi_a,
    const big_integer_t *restrict bi_b);

big_integer_t *big_integer_new(void) {
    big_integer_t *bi = malloc(sizeof(big_integer_t));
    if (bi == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for big_number_t");
        perror(error_msg);
        return nullptr;
    }
    bi->capacity = BIG_INTEGER_DEFAULT_BUFF_SIZE;
    bi->number = calloc(bi->capacity, sizeof(char));
    if (bi->number == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for number buffer");
        perror(error_msg);
        return nullptr;
    }
    bi->number[0] = '0';
    bi->number[1] = '\0';
    bi->length = 1;
    bi->is_negative = false;
    return bi;
}

big_integer_t *big_integer_from_str(const char *number, const size_t capacity) {
    if (number == NULL || capacity == 0) {
        return nullptr;
    }
    big_integer_t *bi = malloc(sizeof(big_integer_t));
    if (bi == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for big_number_t");
        perror(error_msg);
        return nullptr;
    }
    const size_t final_capacity = capacity + 1;
    if (number[0] == '-') {
        bi->is_negative = true;
        number++;
    } else {
        bi->is_negative = false;
    }
    bi->number = calloc(final_capacity, sizeof(char));
    if (bi->number == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for number buffer");
        perror(error_msg);
        return nullptr;
    }
    strncpy(bi->number, number, capacity);
    bi->length = strnlen(bi->number, BIG_INTEGER_MAX_DIGITS);
    bi->capacity = final_capacity;
    return bi;
}

big_integer_t *big_integer_from_ll(const long long number) {
    big_integer_t *bi = big_integer_new();
    bi->number = lltoa(number, &bi->capacity, &bi->length);
    if (number < 0) {
        bi->is_negative = true;
    }
    return bi;
}

big_integer_t *big_integer_from_ull(const unsigned long long number) {
    big_integer_t *bi = big_integer_new();
    bi->number = ulltoa(number, &bi->capacity, &bi->length);
    bi->is_negative = false;
    return bi;
}

void big_integer_free(big_integer_t *bi) {
    free(bi->number);
    free(bi);
}

big_integer_t *big_number_add_internal(
    const big_integer_t *restrict const bi_a,
    const big_integer_t *restrict const bi_b) {
    const char *a = bi_a->number;
    const size_t a_len = bi_a->length;
    const bool is_a_negative = bi_a->is_negative;
    const char *b = bi_b->number;
    const size_t b_len = bi_b->length;
    const bool is_b_negative = bi_b->is_negative;

    big_integer_t *result_bn = big_integer_new();
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
 * @param bi_a The first big number input.
 * @param bi_b The second big number input.
 * @return A new big_number_t structure containing the sum of bn_a and bn_b.
 */
big_integer_t *big_integer_add(
    const big_integer_t *restrict const bi_a,
    const big_integer_t *restrict const bi_b) {
    const size_t a_len = bi_a->length;
    const bool is_a_negative = bi_a->is_negative;
    const size_t b_len = bi_b->length;
    const bool is_b_negative = bi_b->is_negative;
    errno = 0;
    if ((is_a_negative && is_b_negative) || (!is_a_negative && !is_b_negative)) {
        big_integer_t * result = big_number_add_internal(bi_a, bi_b);
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
        const char *a = bi_a->number;
        const char *b = bi_b->number;
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
    const big_integer_t ac = {
        .capacity = bi_a->capacity, .number = bi_a->number, .is_negative = false, .length = bi_a->length
    };
    const big_integer_t bc = {
        .capacity = bi_b->capacity, .number = bi_b->number, .is_negative = false, .length = bi_b->length
    };
    if (is_mod_a_bigger) {
        big_integer_t *result = big_integer_sub_internal(&ac, &bc);
        result->is_negative = out_is_negative;
        return result;
    }
    big_integer_t *result = big_integer_sub_internal(&bc, &ac);
    result->is_negative = out_is_negative;
    return result;
}

/**
 *
 * @param bi_a a where a > b && a > 0
 * @param bi_b b where b < a && b > 0
 * @return val
 */
big_integer_t *big_integer_sub_internal(
    const big_integer_t *restrict const bi_a,
    const big_integer_t *restrict const bi_b) {
    char *const a = strndup(bi_a->number, bi_a->length + 1);
    char *pa = a + bi_a->length - 1;
    char *const b = strndup(bi_b->number, bi_b->length + 1);
    const char *pb = b + bi_b->length - 1;
    const size_t r_cap = bi_a->capacity + 1;
    char *const r = calloc(r_cap, sizeof(char));
    char *pr = r;
    for (size_t i = 0; i < bi_b->length; i++) {
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
    big_integer_t *result = big_integer_from_str(r, r_cap);
    free(r);
    free(b);
    free(a);
    return result;
}

big_integer_t *big_integer_sub(const big_integer_t *bi_a, const big_integer_t *bi_b) {
    const size_t a_len = bi_a->length;
    const size_t b_len = bi_b->length;
    errno = 0;
    bool is_both_equal = true;
    bool is_mod_a_bigger = false;
    if (a_len > b_len) {
        is_mod_a_bigger = true;
        is_both_equal = false;
    } else if (b_len > a_len) {
        is_mod_a_bigger = false;
        is_both_equal = false;
    } else {
        const char *a = bi_a->number;
        const char *b = bi_b->number;
        for (size_t i = 0; i < a_len; i++) {
            if (a[i] > b[i]) {
                is_mod_a_bigger = true;
                is_both_equal = false;
                break;
            }
            if (b[i] > a[i]) {
                is_mod_a_bigger = false;
                is_both_equal = false;
                break;
            }
        }
    }
    const big_integer_t ac = {
        .capacity = bi_a->capacity, .number = bi_a->number, .is_negative = false, .length = bi_a->length
    };
    const big_integer_t bc = {
        .capacity = bi_b->capacity, .number = bi_b->number, .is_negative = false, .length = bi_b->length
    };
    if (is_mod_a_bigger) {
        big_integer_t *result = big_integer_sub_internal(&ac, &bc);
        result->is_negative = bi_a->is_negative;
        return result;
    }
    big_integer_t *result = big_integer_sub_internal(&bc, &ac);
    if (!is_both_equal) {
        if (!bi_a->is_negative) {
            if (!bi_b->is_negative) {
                result->is_negative = true;
            } else {
                result->is_negative = false;
            }
        } else {
            if (!bi_b->is_negative) {
                result->is_negative = false;
            } else {
                result->is_negative = true;
            }
        }
    } else {
        result->is_negative = false;
    }
    return result;
}
