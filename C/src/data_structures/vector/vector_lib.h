//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <sys/_types/_size_t.h>

typedef struct vector {
    size_t capacity;
    size_t num_elements;
    size_t elem_size;
    void *data_buffer;
} vector;

vector *vector_create(const size_t capacity, const size_t elem_size);

typedef enum vector_append_elem_result {
    VECTOR_APPEND_OK = 0,
    VECTOR_APPEND_E_VEC_ARG_NULL = 1,
    VECTOR_APPEND_E_MALLOC = 2,
} vector_append_elem_result;

vector_append_elem_result vector_append_elem(vector **vector_ref, const void *data);

vector *vector_insert_elem_at(vector **vector_ref, const void *data, size_t index);

void *vector_get_elem_at(const vector **vector_ref, const size_t index);

void vector_destroy(vector *vector);

#endif //VECTOR_LIB_H
