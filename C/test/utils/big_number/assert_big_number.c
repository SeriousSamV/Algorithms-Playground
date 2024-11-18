#include <assert.h>
#include <stdlib.h>
#include <big_number.h>
#include <stdio.h>
#include <string.h>

big_number_t *big_number_sub_internal(
    const big_number_t *restrict bn_a,
    const big_number_t *restrict bn_b);

void test_big_number_add() {
    const big_number_t *a = big_number_from_str("12", 2);
    const big_number_t *b = big_number_from_str("24", 2);
    const big_number_t *res = big_number_add(a, b);
    printf("val=%s\n", res->number);
    assert(strcmp(res->number, "36") == 0);
    assert(res->is_negative == false);

    const big_number_t *a1 = big_number_from_str("99", 2);
    const big_number_t *b1 = big_number_from_str("1", 1);
    const big_number_t *res1 = big_number_add(a1, b1);
    printf("val=%s\n", res1->number);
    assert(strcmp(res1->number, "100") == 0);
    assert(res1->is_negative == false);

    const big_number_t *a2 = big_number_from_str("101", 3);
    const big_number_t *b2 = big_number_from_str("1", 1);
    const big_number_t *res2 = big_number_add(a2, b2);
    printf("val=%s\n", res2->number);
    assert(strcmp(res2->number, "102") == 0);
    assert(res2->is_negative == false);

    const big_number_t *a3 = big_number_from_str("-101", 3);
    const big_number_t *b3 = big_number_from_str("-1", 1);
    const big_number_t *res3 = big_number_add(a3, b3);
    printf("val=%s\n", res3->number);
    assert(strcmp(res3->number, "102") == 0);
    assert(res3->is_negative == true);
}

void test_big_number_sub_internal() {
    big_number_t *a = big_number_from_str("12", 2);
    big_number_t *b = big_number_from_str("9", 2);
    big_number_t *r = big_number_sub_internal(a, b);
    assert(r != NULL);
    assert(strcmp(r->number, "3") == 0);
    free(a);
    free(b);
    free(r);

    big_number_t *a1 = big_number_from_str("100", 3);
    big_number_t *b1 = big_number_from_str("1", 1);
    big_number_t *r1 = big_number_sub_internal(a1, b1);
    assert(r1 != NULL);
    assert(strcmp(r1->number, "99") == 0);
    free(a1);
    free(b1);
    free(r1);

    big_number_t *a2 = big_number_from_str("0", 1);
    big_number_t *b2 = big_number_from_str("0", 1);
    big_number_t *r2 = big_number_sub_internal(a2, b2);
    assert(r2 != NULL);
    assert(strcmp(r2->number, "0") == 0);
    free(a2);
    free(b2);
    free(r2);

    big_number_t *a3 = big_number_from_str("1000", 4);
    big_number_t *b3 = big_number_from_str("1", 1);
    big_number_t *r3 = big_number_sub_internal(a3, b3);
    assert(r3 != NULL);
    assert(strcmp(r3->number, "999") == 0);
    free(a3);
    free(b3);
    free(r3);

    big_number_t *a4 = big_number_from_str("5", 1);
    big_number_t *b4 = big_number_from_str("3", 1);
    big_number_t *r4 = big_number_sub_internal(a4, b4);
    assert(r4 != NULL);
    assert(strcmp(r4->number, "2") == 0);
    free(a4);
    free(b4);
    free(r4);
}

int main() {
    test_big_number_add();
    test_big_number_sub_internal();
    return EXIT_SUCCESS;
}
