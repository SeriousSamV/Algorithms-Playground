#include <big_decimal.h>
#include <stdlib.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
#include <stdio.h>
#include <string_utils.h>
#include <string.h>
#include <sys/errno.h>

big_decimal_t *big_decimal_new(const long long number, const long long decimal) {
    big_decimal_t *decimal_p = malloc(sizeof(big_decimal_t));
    decimal_p->number_string = lltoa(number, &decimal_p->number_string_capacity, &decimal_p->number_string_length);
    decimal_p->decimal_string = lltoa(decimal, &decimal_p->decimal_string_capacity, &decimal_p->decimal_string_length);
    return decimal_p;
}

big_decimal_t *big_decimal_from_str(const char *number_str, const size_t number_str_len) {
    if (number_str == NULL || number_str_len == 0) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "number_str is null or number_str_len in 0");
        perror(error_msg);
        return nullptr;
    }
    const char *nsp = number_str;
    bool is_negative = false;
    if (number_str[0] == '-') {
        is_negative = true;
        nsp++;
    }
    char * const num_part = calloc(number_str_len + 1, sizeof(char));
    char * const dec_part = calloc(number_str_len + 1, sizeof(char));
    if (num_part == NULL || dec_part == NULL) {
        char error_msg[BUFSIZ];
        snprintf(error_msg, BUFSIZ, "%s:%d %s: %s\n", __FILE_NAME__, __LINE__, __FUNCTION__,
                 "cannot alloc mem for num_part or dec_part");
        perror(error_msg);
        return nullptr;
    }
    char *write_ptr = num_part;
    while (nsp < number_str + number_str_len || *nsp == '\0') {
        if (*nsp == '.') {
            *write_ptr = '\0';
            write_ptr = dec_part;
        } else {
            *write_ptr = *nsp;
            ++write_ptr;
        }
        *nsp++;
    }
    big_decimal_t *bd = calloc(1, sizeof(big_decimal_t));
    bd->number_string = num_part;
    bd->number_string_capacity = number_str_len + 1;
    bd->number_string_length = strnlen(num_part, number_str_len + 1);
    bd->decimal_string = dec_part;
    bd->decimal_string_capacity = number_str_len + 1;
    bd->decimal_string_length = strnlen(dec_part, number_str_len + 1);
    bd->is_negative = is_negative;
    return bd;
}

void big_decimal_free(big_decimal_t *bd) {
    free(bd->number_string);
    free(bd->decimal_string);
    free(bd);
}
