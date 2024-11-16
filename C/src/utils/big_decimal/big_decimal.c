#include <big_decimal.h>
#include <stdlib.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void reverse_string(char *const str) {
    if (str == NULL) return;
    const size_t len = strlen(str);
    if (len <= 0) return;
    for (size_t i = 0; i < len / 2; i++) {
        const char temp = str[len - 1 - i];
        str[len - 1 - i] = str[i];
        str[i] = temp;
    }
}

char *lltoa(long long value, size_t *const restrict out_capacity, size_t *const restrict out_len) {
    char *buff = calloc(MIN_CAPACITY, sizeof(char));
    *out_capacity = MIN_CAPACITY;
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
    reverse_string(buff);
    return buff;
}

big_decimal_t *big_decimal_new(const long long number, const long long decimal) {
    big_decimal_t *decimal_p = malloc(sizeof(big_decimal_t));
    decimal_p->number_string = lltoa(number, &decimal_p->number_string_capacity, &decimal_p->number_string_length);
    decimal_p->decimal_string = lltoa(decimal, &decimal_p->decimal_string_capacity, &decimal_p->decimal_string_length);
    return decimal_p;
}

/**
 * Adds two numeric strings and returns the result as a newly allocated string.
 *
 * @param a The first number string.
 * @param a_len Length of the first number string.
 * @param is_a_negative Boolean indicating if the first number is negative.
 * @param b The second number string.
 * @param b_len Length of the second number string.
 * @param is_b_negative Boolean indicating if the second number is negative.
 * @param out_len Pointer to store the length of the result.
 * @param out_is_negative Pointer to store whether the result is negative.
 * @return A newly allocated string representing the sum of the two numbers.
 *         If memory allocation fails, returns nullptr.
 */
char *add_number_strings(
    const char *restrict const a,
    const size_t a_len,
    const bool is_a_negative,
    const char *restrict const b,
    const size_t b_len,
    const bool is_b_negative,
    size_t *const restrict out_len,
    bool *const restrict out_is_negative) {
    *out_len = a_len > b_len ? a_len : b_len;
    char *result = calloc(*out_len + 2, sizeof(char));
    if (result == NULL) {
        return nullptr;
    }
    int carry = 0;
    char *result_ptr = result;
    if ((is_a_negative && is_b_negative) || (!is_a_negative && !is_b_negative)) {
        *out_is_negative = (bool) is_a_negative && is_b_negative;
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
    }
    reverse_string(result);
    return result;
}
