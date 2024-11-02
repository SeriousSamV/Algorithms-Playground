#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <vector_lib.h>
#include <nullptr_fix.h>

void test_vector_create_and_append() {
    vector *int_vec = vector_create(1, sizeof(int));
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 0);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data1 = 15;
    const vector_append_elem_result res = vector_append_elem(int_vec, &data1);
    assert(res == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 1);
    assert(*(int *)int_vec->data_buffer == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data2 = 16;
    const vector_append_elem_result res2 = vector_append_elem(int_vec, &data2);
    assert(res2 == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 2);
    assert(int_vec->num_elements == 2);
    assert(*(int *)int_vec->data_buffer == data1);
    assert(*((int *)int_vec->data_buffer + 1) == data2);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data3 = 17;
    const vector_append_elem_result res3 = vector_append_elem(int_vec, &data3);
    assert(res3 == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 4);
    assert(int_vec->num_elements == 3);
    assert(*(int *)int_vec->data_buffer == data1);
    assert(*((int *)int_vec->data_buffer + 1) == data2);
    assert(*((int *)int_vec->data_buffer + 2) == data3);
}

void test_vector_insert_elem_at() {
    vector *int_vec = vector_create(1, sizeof(int));
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 0);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data1 = 15;
    const vector_insert_elem_result res1 = vector_insert_elem_at(int_vec, &data1, 0);
    assert(res1 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 1);
    assert(int_vec->num_elements == 1);
    assert(*(int *)int_vec->data_buffer == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data2 = 14;
    const vector_insert_elem_result res2 = vector_insert_elem_at(int_vec, &data2, 0);
    assert(res2 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 2);
    assert(int_vec->num_elements == 2);
    assert(*(int *)int_vec->data_buffer == data2);
    assert(*((int *)int_vec->data_buffer + 1) == data1);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data3 = 17;
    const vector_insert_elem_result res3 = vector_insert_elem_at(int_vec, &data3, 1);
    assert(res3 == VECTOR_INSERT_OK);
    assert(int_vec->capacity == 4);
    assert(int_vec->num_elements == 3);
    assert(*(int *)int_vec->data_buffer == data2);
    assert(*((int *)int_vec->data_buffer + 1) == data3);
    assert(*((int *)int_vec->data_buffer + 2) == data1);

    vector_destroy(int_vec);
}

void test_vector_get_elem_at() {
    vector *int_vec = vector_create(5, sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        vector_append_elem(int_vec, &arr[i]);
    }
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        const int elem = *((int *)vector_get_elem_at(int_vec, i));
        assert(elem == arr[i]);
    }
    vector_destroy(int_vec);
}

void test_vector_remove_elem_at() {
    vector *int_vec = vector_create(5, sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        vector_append_elem(int_vec, &arr[i]);
    }
    assert(int_vec->num_elements == 5);
    assert(*(int *)vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)vector_get_elem_at(int_vec, 2) == 3);
    assert(*(int *)vector_get_elem_at(int_vec, 3) == 4);
    assert(*(int *)vector_get_elem_at(int_vec, 4) == 5);
    const vector_remove_elem_result res1 = vector_remove_elem_at(int_vec, 2);
    assert(res1 == VECTOR_REMOVE_ELEM_OK);
    assert(int_vec->num_elements == 4);
    assert(*(int *)vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)vector_get_elem_at(int_vec, 2) == 4);
    assert(*(int *)vector_get_elem_at(int_vec, 3) == 5);
    assert(vector_get_elem_at(int_vec, 4) == nullptr);

    const vector_remove_elem_result res2 = vector_remove_elem_at(int_vec, 3);
    assert(res2 == VECTOR_REMOVE_ELEM_OK);
    assert(int_vec->num_elements == 3);
    assert(*(int *)vector_get_elem_at(int_vec, 0) == 1);
    assert(*(int *)vector_get_elem_at(int_vec, 1) == 2);
    assert(*(int *)vector_get_elem_at(int_vec, 2) == 4);
    assert(vector_get_elem_at(int_vec, 3) == nullptr);
    assert(vector_get_elem_at(int_vec, 4) == nullptr);

    vector_destroy(int_vec);
}

int main() {
    test_vector_create_and_append();
    test_vector_insert_elem_at();
    test_vector_get_elem_at();
    test_vector_remove_elem_at();

    return EXIT_SUCCESS;
}
