//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <sys/types.h>

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
    VECTOR_APPEND_E_RESIZE_FAILED = 2,
} vector_append_elem_result;

vector_append_elem_result vector_append_elem(vector *vector, const void *data);

typedef enum vector_insert_elem_result {
    VECTOR_INSERT_OK = 0,
    VECTOR_INSERT_E_VEC_ARG_NULL = 1,
    VECTOR_INSERT_E_RESIZE_FAILED = 2,
    VECTOR_INSERT_E_INDEX_OUT_OF_BOUNDS = 3,
} vector_insert_elem_result;

vector_insert_elem_result vector_insert_elem_at(
    vector *vector,
    const void *data,
    const size_t index);

void *vector_get_elem_at(const vector *vector, const size_t index);

typedef enum vector_remove_elem_result {
    VECTOR_REMOVE_ELEM_OK = 0,
    VECTOR_REMOVE_ELEM_E_VEC_ARG_NULL = 1,
    VECTOR_REMOVE_ELEM_E_INDEX_OUT_OF_BOUNDS = 2,
} vector_remove_elem_result;

vector_remove_elem_result vector_remove_elem_at(vector *vector, size_t index);

void vector_destroy(vector *vector);

#endif //VECTOR_LIB_H
