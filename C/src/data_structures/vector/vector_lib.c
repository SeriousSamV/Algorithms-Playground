#include <vector_lib.h>
#include <nullptr_fix.h>
#include <stdio.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>
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

bool check_and_resize(vector *vector, const size_t capacity_need) {
    if (capacity_need > SIZE_MAX) {
        perror("capacity need is greater than SIZE_MAX");
        return false;
    }
    if (vector->capacity >= capacity_need) {
        return true;
    }
    const size_t new_capacity = vector->capacity * 2;
    void *new_buffer = realloc(vector->data_buffer, new_capacity * vector->elem_size);
    if (new_buffer == nullptr) {
        perror("cannot alloc mem for vec");
        return false;
    }
    vector->data_buffer = new_buffer;
    vector->capacity = new_capacity;

    return true;
}

vector_append_elem_result vector_append_elem(vector *vector, const void *data) {
    if (vector == nullptr) {
        fprintf(stderr, "cannot append element to null vector\n");
        fflush(stderr);
        return VECTOR_APPEND_E_VEC_ARG_NULL;
    }
    if (!check_and_resize(vector, vector->num_elements + 1)) {
        return VECTOR_APPEND_E_RESIZE_FAILED;
    }
    memcpy(vector->data_buffer + vector->num_elements * vector->elem_size, data, vector->elem_size);
    vector->num_elements++;
    return VECTOR_APPEND_OK;
}

vector_insert_elem_result vector_insert_elem_at(
    vector *vector,
    const void *data,
    const size_t index) {
    if (vector == nullptr) {
        fprintf(stderr, "cannot append element to null vector\n");
        fflush(stderr);
        return VECTOR_INSERT_E_VEC_ARG_NULL;
    }
    if (index > vector->num_elements) {
        fprintf(stderr, "index out of bounds\n");
        fflush(stderr);
        return VECTOR_INSERT_E_INDEX_OUT_OF_BOUNDS;
    }
    if (!check_and_resize(vector, vector->num_elements + 1)) {
        return VECTOR_INSERT_E_RESIZE_FAILED;
    }
    memmove((char *) vector->data_buffer + (index + 1) * vector->elem_size,
            (char *) vector->data_buffer + index * vector->elem_size,
            (vector->num_elements - index) * vector->elem_size);
    memcpy((char *) vector->data_buffer + index * vector->elem_size, data, vector->elem_size);
    vector->num_elements++;
    return VECTOR_INSERT_OK;
}

void *vector_get_elem_at(const vector *vector, const size_t index) {
    if (vector == nullptr) {
        fprintf(stderr, "cannot get element at null vector\n");
        fflush(stderr);
        return nullptr;
    }
    if (vector->num_elements <= index) {
        fprintf(stderr, "index out of bounds\n");
        fflush(stderr);
        return nullptr;
    }
    return vector->data_buffer + (index * vector->elem_size);
}

vector_remove_elem_result vector_remove_elem_at(vector *vector, size_t index) {
    if (vector == nullptr) {
        return VECTOR_REMOVE_ELEM_E_VEC_ARG_NULL;
    }
    if (vector->num_elements <= index) {
        return VECTOR_REMOVE_ELEM_E_INDEX_OUT_OF_BOUNDS;
    }
    if (vector->num_elements == index + 1) {
        memset((char *) vector->data_buffer + index * vector->elem_size, 0, vector->elem_size);
        vector->num_elements--;
        return VECTOR_REMOVE_ELEM_OK;
    }
    memmove((char *) vector->data_buffer + index * vector->elem_size,
            (char *) vector->data_buffer + (index + 1) * vector->elem_size,
            (vector->num_elements - index - 1) * vector->elem_size);
    bzero((char *) vector->data_buffer + (vector->num_elements - 1) * vector->elem_size, vector->elem_size);
    vector->num_elements--;
    return VECTOR_REMOVE_ELEM_OK;
}

void vector_destroy(vector *vector) {
    free(vector->data_buffer);
    free(vector);
}
