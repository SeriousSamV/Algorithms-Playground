#include <assert.h>
#include <stdlib.h>
#include <big_integer.h>
#include <string.h>
// ReSharper disable CppUnusedIncludeDirective
#include <stdbool.h>
// ReSharper restore CppUnusedIncludeDirective

big_integer_t *big_integer_sub_internal(
    const big_integer_t *restrict bi_a,
    const big_integer_t *restrict bi_b);

void test_big_integer_add() {
    big_integer_t *a = big_integer_from_str("12", 2);
    big_integer_t *b = big_integer_from_str("24", 2);
    big_integer_t *res = big_integer_add(a, b);
    assert(strcmp(res->number, "36") == 0);
    assert(res->is_negative == false);
    big_integer_free(res);
    big_integer_free(b);
    big_integer_free(a);

    big_integer_t *a1 = big_integer_from_str("99", 2);
    big_integer_t *b1 = big_integer_from_str("1", 1);
    big_integer_t *res1 = big_integer_add(a1, b1);
    assert(strcmp(res1->number, "100") == 0);
    assert(res1->is_negative == false);
    big_integer_free(res1);
    big_integer_free(b1);
    big_integer_free(a1);

    big_integer_t *a2 = big_integer_from_str("101", 3);
    big_integer_t *b2 = big_integer_from_str("1", 1);
    big_integer_t *res2 = big_integer_add(a2, b2);
    assert(strcmp(res2->number, "102") == 0);
    assert(res2->is_negative == false);
    big_integer_free(res2);
    big_integer_free(b2);
    big_integer_free(a2);

    big_integer_t *a3 = big_integer_from_str("-101", 3);
    big_integer_t *b3 = big_integer_from_str("-1", 1);
    big_integer_t *res3 = big_integer_add(a3, b3);
    assert(strcmp(res3->number, "102") == 0);
    assert(res3->is_negative == true);
    big_integer_free(res3);
    big_integer_free(b3);
    big_integer_free(a3);

    big_integer_t *a4 = big_integer_from_str("-12", 2);
    big_integer_t *b4 = big_integer_from_str("24", 2);
    big_integer_t *res4 = big_integer_add(a4, b4);
    assert(strcmp(res4->number, "12") == 0);
    assert(res4->is_negative == false);
    big_integer_free(res4);
    big_integer_free(b4);
    big_integer_free(a4);

    big_integer_t *a5 = big_integer_from_str("-99", 2);
    big_integer_t *b5 = big_integer_from_str("1", 1);
    big_integer_t *res5 = big_integer_add(a5, b5);
    assert(strcmp(res5->number, "98") == 0);
    assert(res5->is_negative == true);
    big_integer_free(res5);
    big_integer_free(b5);
    big_integer_free(a5);

    big_integer_t *a6 = big_integer_from_str("50", 2);
    big_integer_t *b6 = big_integer_from_str("-50", 2);
    big_integer_t *res6 = big_integer_add(a6, b6);
    assert(strcmp(res6->number, "0") == 0);
    assert(res6->is_negative == false);
    big_integer_free(res6);
    big_integer_free(b6);
    big_integer_free(a6);

    big_integer_t *a7 = big_integer_from_str("-50", 2);
    big_integer_t *b7 = big_integer_from_str("50", 2);
    big_integer_t *res7 = big_integer_add(a7, b7);
    assert(strcmp(res7->number, "0") == 0);
    assert(res7->is_negative == false);
    big_integer_free(res7);
    big_integer_free(b7);
    big_integer_free(a7);

    big_integer_t *a8 = big_integer_from_str("-123", 3);
    big_integer_t *b8 = big_integer_from_str("23", 2);
    big_integer_t *res8 = big_integer_add(a8, b8);
    assert(strcmp(res8->number, "100") == 0);
    assert(res8->is_negative == true);
    big_integer_free(res8);
    big_integer_free(b8);
    big_integer_free(a8);

    big_integer_t *a9 = big_integer_from_str("123", 3);
    big_integer_t *b9 = big_integer_from_str("-23", 2);
    big_integer_t *res9 = big_integer_add(a9, b9);
    assert(strcmp(res9->number, "100") == 0);
    assert(res9->is_negative == false);
    big_integer_free(res9);
    big_integer_free(b9);
    big_integer_free(a9);
}

void test_big_integer_sub_internal() {
    big_integer_t *a = big_integer_from_str("12", 2);
    big_integer_t *b = big_integer_from_str("9", 2);
    big_integer_t *r = big_integer_sub_internal(a, b);
    assert(r != NULL);
    assert(strcmp(r->number, "3") == 0);
    big_integer_free(a);
    big_integer_free(b);
    big_integer_free(r);

    big_integer_t *a1 = big_integer_from_str("100", 3);
    big_integer_t *b1 = big_integer_from_str("1", 1);
    big_integer_t *r1 = big_integer_sub_internal(a1, b1);
    assert(r1 != NULL);
    assert(strcmp(r1->number, "99") == 0);
    big_integer_free(a1);
    big_integer_free(b1);
    big_integer_free(r1);

    big_integer_t *a2 = big_integer_from_str("0", 1);
    big_integer_t *b2 = big_integer_from_str("0", 1);
    big_integer_t *r2 = big_integer_sub_internal(a2, b2);
    assert(r2 != NULL);
    assert(strcmp(r2->number, "0") == 0);
    big_integer_free(a2);
    big_integer_free(b2);
    big_integer_free(r2);

    big_integer_t *a3 = big_integer_from_str("1000", 4);
    big_integer_t *b3 = big_integer_from_str("1", 1);
    big_integer_t *r3 = big_integer_sub_internal(a3, b3);
    assert(r3 != NULL);
    assert(strcmp(r3->number, "999") == 0);
    big_integer_free(a3);
    big_integer_free(b3);
    big_integer_free(r3);

    big_integer_t *a4 = big_integer_from_str("5", 1);
    big_integer_t *b4 = big_integer_from_str("3", 1);
    big_integer_t *r4 = big_integer_sub_internal(a4, b4);
    assert(r4 != NULL);
    assert(strcmp(r4->number, "2") == 0);
    big_integer_free(a4);
    big_integer_free(b4);
    big_integer_free(r4);

    big_integer_t *a5 = big_integer_from_str("10100", 5);
    big_integer_t *b5 = big_integer_from_str("9", 1);
    big_integer_t *r5 = big_integer_sub_internal(a5, b5); // "19001"
    assert(r5 != NULL);
    assert(strcmp(r5->number, "10091") == 0);
    big_integer_free(a5);
    big_integer_free(b5);
    big_integer_free(r5);

    big_integer_t *a6 = big_integer_from_str("456", 3);
    big_integer_t *b6 = big_integer_from_str("123", 3);
    big_integer_t *r6 = big_integer_sub_internal(a6, b6);
    assert(r6 != NULL);
    assert(strcmp(r6->number, "333") == 0);
    big_integer_free(a6);
    big_integer_free(b6);
    big_integer_free(r6);

    big_integer_t *a7 = big_integer_from_str("1001", 4);
    big_integer_t *b7 = big_integer_from_str("2", 1);
    big_integer_t *r7 = big_integer_sub_internal(a7, b7);
    assert(r7 != NULL);
    assert(strcmp(r7->number, "999") == 0);
    big_integer_free(a7);
    big_integer_free(b7);
    big_integer_free(r7);

    big_integer_t *a8 = big_integer_from_str("2000", 4);
    big_integer_t *b8 = big_integer_from_str("1999", 4);
    big_integer_t *r8 = big_integer_sub_internal(a8, b8);
    assert(r8 != NULL);
    assert(strcmp(r8->number, "1") == 0);
    big_integer_free(a8);
    big_integer_free(b8);
    big_integer_free(r8);

    big_integer_t *a9 = big_integer_from_str("1500", 4);
    big_integer_t *b9 = big_integer_from_str("500", 3);
    big_integer_t *r9 = big_integer_sub_internal(a9, b9);
    assert(r9 != NULL);
    assert(strcmp(r9->number, "1000") == 0);
    big_integer_free(a9);
    big_integer_free(b9);
    big_integer_free(r9);

    big_integer_t *a10 = big_integer_from_str("5402", 4);
    big_integer_t *b10 = big_integer_from_str("1234", 4);
    big_integer_t *r10 = big_integer_sub_internal(a10, b10);
    assert(r10 != NULL);
    assert(strcmp(r10->number, "4168") == 0);
    big_integer_free(a10);
    big_integer_free(b10);
    big_integer_free(r10);
}

void test_big_integer_sub() {
    big_integer_t *a1 = big_integer_from_str("1", 1);
    big_integer_t *b1 = big_integer_from_str("0", 1);
    big_integer_t *r1 = big_integer_sub(a1, b1);
    assert(r1 != NULL);
    assert(strcmp(r1->number, "1") == 0);
    assert(r1->is_negative == false);
    big_integer_free(r1);
    big_integer_free(b1);
    big_integer_free(a1);

    big_integer_t *a2 = big_integer_from_str("25", 2);
    big_integer_t *b2 = big_integer_from_str("5", 1);
    big_integer_t *r2 = big_integer_sub(a2, b2);
    assert(r2 != NULL);
    assert(strcmp(r2->number, "20") == 0);
    assert(r2->is_negative == false);
    big_integer_free(r2);
    big_integer_free(b2);
    big_integer_free(a2);

    big_integer_t *a3 = big_integer_from_str("1000", 4);
    big_integer_t *b3 = big_integer_from_str("500", 3);
    big_integer_t *r3 = big_integer_sub(a3, b3);
    assert(r3 != NULL);
    assert(strcmp(r3->number, "500") == 0);
    assert(r3->is_negative == false);
    big_integer_free(r3);
    big_integer_free(b3);
    big_integer_free(a3);

    big_integer_t *a4 = big_integer_from_str("12345", 5);
    big_integer_t *b4 = big_integer_from_str("6789", 4);
    big_integer_t *r4 = big_integer_sub(a4, b4);
    assert(r4 != NULL);
    assert(strcmp(r4->number, "5556") == 0);
    assert(r4->is_negative == false);
    big_integer_free(r4);
    big_integer_free(b4);
    big_integer_free(a4);

    big_integer_t *a5 = big_integer_from_str("100", 3);
    big_integer_t *b5 = big_integer_from_str("100", 3);
    big_integer_t *r5 = big_integer_sub(a5, b5);
    assert(r5 != NULL);
    assert(strcmp(r5->number, "0") == 0);
    assert(r5->is_negative == false);
    big_integer_free(r5);
    big_integer_free(b5);
    big_integer_free(a5);

    big_integer_t *a6 = big_integer_from_str("9999", 4);
    big_integer_t *b6 = big_integer_from_str("1", 1);
    big_integer_t *r6 = big_integer_sub(a6, b6);
    assert(r6 != NULL);
    assert(strcmp(r6->number, "9998") == 0);
    assert(r6->is_negative == false);
    big_integer_free(r6);
    big_integer_free(b6);
    big_integer_free(a6);

    big_integer_t *a7 = big_integer_from_str("1", 1);
    big_integer_t *b7 = big_integer_from_str("2", 1);
    big_integer_t *r7 = big_integer_sub(a7, b7);
    assert(r7 != NULL);
    assert(strcmp(r7->number, "1") == 0);
    assert(r7->is_negative == true);
    big_integer_free(r7);
    big_integer_free(b7);
    big_integer_free(a7);

    big_integer_t *a8 = big_integer_from_str("1000", 4);
    big_integer_t *b8 = big_integer_from_str("1001", 4);
    big_integer_t *r8 = big_integer_sub(a8, b8);
    assert(r8 != NULL);
    assert(strcmp(r8->number, "1") == 0);
    assert(r8->is_negative == true);
    big_integer_free(r8);
    big_integer_free(b8);
    big_integer_free(a8);

    big_integer_t *a9 = big_integer_from_str("987654321", 9);
    big_integer_t *b9 = big_integer_from_str("987654321", 9);
    big_integer_t *r9 = big_integer_sub(a9, b9);
    assert(r9 != NULL);
    assert(strcmp(r9->number, "0") == 0);
    assert(r9->is_negative == false);
    big_integer_free(r9);
    big_integer_free(b9);
    big_integer_free(a9);

    big_integer_t *a10 = big_integer_from_str("1000000", 7);
    big_integer_t *b10 = big_integer_from_str("1000001", 7);
    big_integer_t *r10 = big_integer_sub(a10, b10);
    assert(r10 != NULL);
    assert(strcmp(r10->number, "1") == 0);
    assert(r10->is_negative == true);
    big_integer_free(r10);
    big_integer_free(b10);
    big_integer_free(a10);

    big_integer_t *a11 = big_integer_from_str("0012345", 7);
    big_integer_t *b11 = big_integer_from_str("0006789", 7);
    big_integer_t *r11 = big_integer_sub(a11, b11);
    assert(r11 != NULL);
    assert(strcmp(r11->number, "5556") == 0);
    assert(r11->is_negative == false);
    big_integer_free(r11);
    big_integer_free(b11);
    big_integer_free(a11);

    big_integer_t *a12 = big_integer_from_str("1000000000000000000000000000000", 31);
    big_integer_t *b12 = big_integer_from_str("999999999999999999999999999999", 30);
    big_integer_t *r12 = big_integer_sub(a12, b12);
    assert(r12 != NULL);
    assert(strcmp(r12->number, "1") == 0);
    assert(r12->is_negative == false);
    big_integer_free(r12);
    big_integer_free(b12);
    big_integer_free(a12);

    big_integer_t *a13 = big_integer_from_str("999", 3);
    big_integer_t *b13 = big_integer_from_str("1000", 4);
    big_integer_t *r13 = big_integer_sub(a13, b13);
    assert(r13 != NULL);
    assert(strcmp(r13->number, "1") == 0);
    assert(r13->is_negative == true);
    big_integer_free(r13);
    big_integer_free(b13);
    big_integer_free(a13);

    big_integer_t *a14 = big_integer_from_str("1000000000000000000", 19);
    big_integer_t *b14 = big_integer_from_str("2000000000000000001", 19);
    big_integer_t *r14 = big_integer_sub(a14, b14);
    assert(r14 != NULL);
    assert(strcmp(r14->number, "1000000000000000001") == 0);
    assert(r14->is_negative == true);
    big_integer_free(r14);
    big_integer_free(b14);
    big_integer_free(a14);

    big_integer_t *a15 = big_integer_from_str("5000000000000000000000000000000", 31);
    big_integer_t *b15 = big_integer_from_str("10000000000000000000000000000000", 32);
    big_integer_t *r15 = big_integer_sub(a15, b15);
    assert(r15 != NULL);
    assert(strcmp(r15->number, "5000000000000000000000000000000") == 0);
    assert(r15->is_negative == true);
    big_integer_free(r15);
    big_integer_free(b15);
    big_integer_free(a15);

    big_integer_t *a16 = big_integer_from_str("1234567890123456789012345678901", 31);
    big_integer_t *b16 = big_integer_from_str("2234567890123456789012345678901", 31);
    big_integer_t *r16 = big_integer_sub(a16, b16);
    assert(r16 != NULL);
    assert(strcmp(r16->number, "1000000000000000000000000000000") == 0);
    assert(r16->is_negative == true);
    big_integer_free(r16);
    big_integer_free(b16);
    big_integer_free(a16);
}

int main() {
    test_big_integer_add();
    test_big_integer_sub_internal();
    test_big_integer_sub();
    return EXIT_SUCCESS;
}
