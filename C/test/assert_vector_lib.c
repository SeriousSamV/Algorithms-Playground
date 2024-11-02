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

int main() {
    test_vector_create_and_append();
    test_vector_insert_elem_at();

    return EXIT_SUCCESS;
}
