#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <vector_lib.h>
#include <nullptr_fix.h>

void test_vector_create_and_append() {
    vector *int_vec = vector_create(10, sizeof(int));
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 10);
    assert(int_vec->num_elements == 0);

    // ReSharper disable once CppVariableCanBeMadeConstexpr
    const int data1 = 15;
    const vector_append_elem_result res = vector_append_elem(&int_vec, &data1);
    assert(res == VECTOR_APPEND_OK);
    assert(int_vec->elem_size == sizeof(int));
    assert(int_vec->capacity == 10);
    assert(int_vec->num_elements == 1);
    assert(*(int *)int_vec->data_buffer == data1);
}

int main() {
    test_vector_create_and_append();

    return EXIT_SUCCESS;
}
