#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <vector_lib.h>
#include <nullptr_fix.h>

void test_vector_create_and_append() {
    ap_vector_t *int_vec = ap_vector_create(1, sizeof(int));
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 0);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data1 = 15;
    const ap_vector_append_elem_result res = ap_vector_append_elem(int_vec, &data1);
    assert(res == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 1);
    assert(*(int *)int_vec->data_buffer == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data2 = 16;
    const ap_vector_append_elem_result res2 = ap_vector_append_elem(int_vec, &data2);
    assert(res2 == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 2);
    assert(int_vec->num_elements == 2);
    assert(*(int *)int_vec->data_buffer == data1);
    assert(*((int *)int_vec->data_buffer + 1) == data2);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data3 = 17;
    const ap_vector_append_elem_result res3 = ap_vector_append_elem(int_vec, &data3);
    assert(res3 == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 4);
    assert(int_vec->num_elements == 3);
    assert(*(int *)int_vec->data_buffer == data1);
    assert(*((int *)int_vec->data_buffer + 1) == data2);
    assert(*((int *)int_vec->data_buffer + 2) == data3);
}

void test_vector_insert_elem_at() {
    ap_vector_t *int_vec = ap_vector_create(1, sizeof(int));
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 0);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data1 = 15;
    const ap_vector_insert_elem_result res1 = ap_vector_insert_elem_at(int_vec, &data1, 0);
    assert(res1 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 1);
    assert(*(int *)int_vec->data_buffer == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data2 = 14;
    const ap_vector_insert_elem_result res2 = ap_vector_insert_elem_at(int_vec, &data2, 0);
    assert(res2 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 2);
    assert(int_vec->num_elements == 2);
    assert(*(int *)int_vec->data_buffer == data2);
    assert(*((int *)int_vec->data_buffer + 1) == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data3 = 17;
    const ap_vector_insert_elem_result res3 = ap_vector_insert_elem_at(int_vec, &data3, 1);
    assert(res3 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 4);
    assert(int_vec->num_elements == 3);
    assert(*(int *)int_vec->data_buffer == data2);
    assert(*((int *)int_vec->data_buffer + 1) == data3);
    assert(*((int *)int_vec->data_buffer + 2) == data1);

    ap_vector_destroy(int_vec);
}

void test_vector_get_elem_at() {
    ap_vector_t *int_vec = ap_vector_create(5, sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        ap_vector_append_elem(int_vec, &arr[i]);
    }
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        const int elem = *((int *)ap_vector_get_elem_at(int_vec, i));
        assert(elem == arr[i]);
    }
    ap_vector_destroy(int_vec);
}

void test_vector_remove_elem_at() {
    ap_vector_t *int_vec = ap_vector_create(5, sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        ap_vector_append_elem(int_vec, &arr[i]);
    }
    assert(int_vec->num_elements == 5);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 2) == 3);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 3) == 4);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 4) == 5);
    const ap_vector_remove_elem_result res1 = ap_vector_remove_elem_at(int_vec, 2);
    assert(res1 == VECTOR_REMOVE_ELEM_OK);
    assert(int_vec->num_elements == 4);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 2) == 4);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 3) == 5);
    assert(ap_vector_get_elem_at(int_vec, 4) == nullptr);

    const ap_vector_remove_elem_result res2 = ap_vector_remove_elem_at(int_vec, 3);
    assert(res2 == VECTOR_REMOVE_ELEM_OK);
    assert(int_vec->num_elements == 3);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)ap_vector_get_elem_at(int_vec, 2) == 4);
    assert(ap_vector_get_elem_at(int_vec, 3) == nullptr);
    assert(ap_vector_get_elem_at(int_vec, 4) == nullptr);

    ap_vector_destroy(int_vec);
}

int main() {
    test_vector_create_and_append();
    test_vector_insert_elem_at();
    test_vector_get_elem_at();
    test_vector_remove_elem_at();

    return EXIT_SUCCESS;
}
