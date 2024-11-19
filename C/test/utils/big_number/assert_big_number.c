#include <assert.h>
#include <stdlib.h>
#include <big_number.h>
#include <string.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

big_number_t *big_number_sub_internal(
    const big_number_t *restrict bn_a,
    const big_number_t *restrict bn_b);

void test_big_number_add() {
    big_number_t *a = big_number_from_str("12", 2);
    big_number_t *b = big_number_from_str("24", 2);
    big_number_t *res = big_number_add(a, b);
    assert(strcmp(res->number, "36") == 0);
    assert(res->is_negative == false);
    big_number_free(res);
    big_number_free(b);
    big_number_free(a);

    big_number_t *a1 = big_number_from_str("99", 2);
    big_number_t *b1 = big_number_from_str("1", 1);
    big_number_t *res1 = big_number_add(a1, b1);
    assert(strcmp(res1->number, "100") == 0);
    assert(res1->is_negative == false);
    big_number_free(res1);
    big_number_free(b1);
    big_number_free(a1);

    big_number_t *a2 = big_number_from_str("101", 3);
    big_number_t *b2 = big_number_from_str("1", 1);
    big_number_t *res2 = big_number_add(a2, b2);
    assert(strcmp(res2->number, "102") == 0);
    assert(res2->is_negative == false);
    big_number_free(res2);
    big_number_free(b2);
    big_number_free(a2);

    big_number_t *a3 = big_number_from_str("-101", 3);
    big_number_t *b3 = big_number_from_str("-1", 1);
    big_number_t *res3 = big_number_add(a3, b3);
    assert(strcmp(res3->number, "102") == 0);
    assert(res3->is_negative == true);
    big_number_free(res3);
    big_number_free(b3);
    big_number_free(a3);

    big_number_t *a4 = big_number_from_str("-12", 2);
    big_number_t *b4 = big_number_from_str("24", 2);
    big_number_t *res4 = big_number_add(a4, b4);
    assert(strcmp(res4->number, "12") == 0);
    assert(res4->is_negative == false);
    big_number_free(res4);
    big_number_free(b4);
    big_number_free(a4);

    big_number_t *a5 = big_number_from_str("-99", 2);
    big_number_t *b5 = big_number_from_str("1", 1);
    big_number_t *res5 = big_number_add(a5, b5);
    assert(strcmp(res5->number, "98") == 0);
    assert(res5->is_negative == true);
    big_number_free(res5);
    big_number_free(b5);
    big_number_free(a5);

    big_number_t *a6 = big_number_from_str("50", 2);
    big_number_t *b6 = big_number_from_str("-50", 2);
    big_number_t *res6 = big_number_add(a6, b6);
    assert(strcmp(res6->number, "0") == 0);
    assert(res6->is_negative == false);
    big_number_free(res6);
    big_number_free(b6);
    big_number_free(a6);

    big_number_t *a7 = big_number_from_str("-50", 2);
    big_number_t *b7 = big_number_from_str("50", 2);
    big_number_t *res7 = big_number_add(a7, b7);
    assert(strcmp(res7->number, "0") == 0);
    assert(res7->is_negative == false);
    big_number_free(res7);
    big_number_free(b7);
    big_number_free(a7);

    big_number_t *a8 = big_number_from_str("-123", 3);
    big_number_t *b8 = big_number_from_str("23", 2);
    big_number_t *res8 = big_number_add(a8, b8);
    assert(strcmp(res8->number, "100") == 0);
    assert(res8->is_negative == true);
    big_number_free(res8);
    big_number_free(b8);
    big_number_free(a8);

    big_number_t *a9 = big_number_from_str("123", 3);
    big_number_t *b9 = big_number_from_str("-23", 2);
    big_number_t *res9 = big_number_add(a9, b9);
    assert(strcmp(res9->number, "100") == 0);
    assert(res9->is_negative == false);
    big_number_free(res9);
    big_number_free(b9);
    big_number_free(a9);
}

void test_big_number_sub_internal() {
    big_number_t *a = big_number_from_str("12", 2);
    big_number_t *b = big_number_from_str("9", 2);
    big_number_t *r = big_number_sub_internal(a, b);
    assert(r != NULL);
    assert(strcmp(r->number, "3") == 0);
    big_number_free(a);
    big_number_free(b);
    big_number_free(r);

    big_number_t *a1 = big_number_from_str("100", 3);
    big_number_t *b1 = big_number_from_str("1", 1);
    big_number_t *r1 = big_number_sub_internal(a1, b1);
    assert(r1 != NULL);
    assert(strcmp(r1->number, "99") == 0);
    big_number_free(a1);
    big_number_free(b1);
    big_number_free(r1);

    big_number_t *a2 = big_number_from_str("0", 1);
    big_number_t *b2 = big_number_from_str("0", 1);
    big_number_t *r2 = big_number_sub_internal(a2, b2);
    assert(r2 != NULL);
    assert(strcmp(r2->number, "0") == 0);
    big_number_free(a2);
    big_number_free(b2);
    big_number_free(r2);

    big_number_t *a3 = big_number_from_str("1000", 4);
    big_number_t *b3 = big_number_from_str("1", 1);
    big_number_t *r3 = big_number_sub_internal(a3, b3);
    assert(r3 != NULL);
    assert(strcmp(r3->number, "999") == 0);
    big_number_free(a3);
    big_number_free(b3);
    big_number_free(r3);

    big_number_t *a4 = big_number_from_str("5", 1);
    big_number_t *b4 = big_number_from_str("3", 1);
    big_number_t *r4 = big_number_sub_internal(a4, b4);
    assert(r4 != NULL);
    assert(strcmp(r4->number, "2") == 0);
    big_number_free(a4);
    big_number_free(b4);
    big_number_free(r4);

    big_number_t *a5 = big_number_from_str("10100", 5);
    big_number_t *b5 = big_number_from_str("9", 1);
    big_number_t *r5 = big_number_sub_internal(a5, b5); // "19001"
    assert(r5 != NULL);
    assert(strcmp(r5->number, "10091") == 0);
    big_number_free(a5);
    big_number_free(b5);
    big_number_free(r5);

    big_number_t *a6 = big_number_from_str("456", 3);
    big_number_t *b6 = big_number_from_str("123", 3);
    big_number_t *r6 = big_number_sub_internal(a6, b6);
    assert(r6 != NULL);
    assert(strcmp(r6->number, "333") == 0);
    big_number_free(a6);
    big_number_free(b6);
    big_number_free(r6);

    big_number_t *a7 = big_number_from_str("1001", 4);
    big_number_t *b7 = big_number_from_str("2", 1);
    big_number_t *r7 = big_number_sub_internal(a7, b7);
    assert(r7 != NULL);
    assert(strcmp(r7->number, "999") == 0);
    big_number_free(a7);
    big_number_free(b7);
    big_number_free(r7);

    big_number_t *a8 = big_number_from_str("2000", 4);
    big_number_t *b8 = big_number_from_str("1999", 4);
    big_number_t *r8 = big_number_sub_internal(a8, b8);
    assert(r8 != NULL);
    assert(strcmp(r8->number, "1") == 0);
    big_number_free(a8);
    big_number_free(b8);
    big_number_free(r8);

    big_number_t *a9 = big_number_from_str("1500", 4);
    big_number_t *b9 = big_number_from_str("500", 3);
    big_number_t *r9 = big_number_sub_internal(a9, b9);
    assert(r9 != NULL);
    assert(strcmp(r9->number, "1000") == 0);
    big_number_free(a9);
    big_number_free(b9);
    big_number_free(r9);

    big_number_t *a10 = big_number_from_str("5402", 4);
    big_number_t *b10 = big_number_from_str("1234", 4);
    big_number_t *r10 = big_number_sub_internal(a10, b10);
    assert(r10 != NULL);
    assert(strcmp(r10->number, "4168") == 0);
    big_number_free(a10);
    big_number_free(b10);
    big_number_free(r10);
}

int main() {
    test_big_number_add();
    test_big_number_sub_internal();
    return EXIT_SUCCESS;
}
