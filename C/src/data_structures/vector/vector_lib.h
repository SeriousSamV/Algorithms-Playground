//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <sys/types.h>

typedef struct ap_vector {
    size_t capacity;
    size_t num_elements;
    size_t elem_size;
    void *data_buffer;
} ap_vector_t;

ap_vector_t *ap_vector_create(const size_t capacity, const size_t elem_size);

typedef enum ap_vector_append_elem_result {
    VECTOR_APPEND_OK = 0,
    VECTOR_APPEND_E_VEC_ARG_NULL = 1,
    VECTOR_APPEND_E_RESIZE_FAILED = 2,
} ap_vector_append_elem_result;

ap_vector_append_elem_result ap_vector_append_elem(ap_vector_t *vector, const void *data);

typedef enum ap_vector_insert_elem_result {
    VECTOR_INSERT_OK = 0,
    VECTOR_INSERT_E_VEC_ARG_NULL = 1,
    VECTOR_INSERT_E_RESIZE_FAILED = 2,
    VECTOR_INSERT_E_INDEX_OUT_OF_BOUNDS = 3,
} ap_vector_insert_elem_result;

ap_vector_insert_elem_result ap_vector_insert_elem_at(
    ap_vector_t *vector,
    const void *data,
    const size_t index);

void *ap_vector_get_elem_at(const ap_vector_t *vector, const size_t index);

typedef enum ap_vector_remove_elem_result {
    VECTOR_REMOVE_ELEM_OK = 0,
    VECTOR_REMOVE_ELEM_E_VEC_ARG_NULL = 1,
    VECTOR_REMOVE_ELEM_E_INDEX_OUT_OF_BOUNDS = 2,
} ap_vector_remove_elem_result;

ap_vector_remove_elem_result ap_vector_remove_elem_at(ap_vector_t *vector, size_t index);

void ap_vector_destroy(ap_vector_t *vector);

#endif //VECTOR_LIB_H
