#include <vector_lib.h>
#include <nullptr_fix.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


vector *vector_create(const size_t capacity, const size_t elem_size) {
    vector *vector = calloc(1, sizeof(*vector));
    vector->capacity = capacity;
    vector->num_elements = 0;
    vector->elem_size = elem_size;
    vector->data_buffer = calloc(capacity, elem_size);
    if (vector->data_buffer == nullptr) {
        perror("cannot alloc mem for vec");
        free(vector);
        return nullptr;
    }
    return vector;
}

vector_append_elem_result vector_append_elem(vector **vector_ref, const void *data) {
    vector *vector = vector_ref != nullptr ? *vector_ref : nullptr;
    if (vector == nullptr) {
        fprintf(stderr, "cannot append element to null vector\n");
        fflush(stderr);
        return VECTOR_APPEND_E_VEC_ARG_NULL;
    }
    if (vector->num_elements == vector->capacity) {
        const size_t new_capacity = vector->capacity * 2;
        void *new_buffer = realloc(vector->data_buffer, new_capacity * vector->elem_size);
        if (new_buffer == nullptr) {
            perror("cannot alloc mem for vec");
            return VECTOR_APPEND_E_MALLOC;
        }
        vector->data_buffer = new_buffer;
    }
    memcpy(vector->data_buffer + vector->num_elements * vector->elem_size, data, vector->elem_size);
    vector->num_elements++;
    return VECTOR_APPEND_OK;
}

void vector_destroy(vector *vector) {
    free(vector->data_buffer);
    free(vector);
}
