#ifndef STACK_LIB_H
#define STACK_LIB_H

#include <vector_lib.h>

typedef struct ap_stack {
    ap_vector_t *storage;
    size_t top_index;
} ap_stack_t;

ap_stack_t *ap_stack_create(const size_t initial_capacity, const size_t element_size);

typedef enum ap_stack_push_result {
    STACK_PUSH_OK = 0,
    STACK_PUSH_E_STACK_ARG_NULL = 1,
    STACK_PUSH_E_STORAGE = 2,
} ap_stack_push_result;

ap_stack_push_result ap_stack_push(ap_stack_t *stack, const void *element);

typedef enum ap_stack_pop_result {
    STACK_POP_OK = 0,
    STACK_POP_E_EMPTY = 1,
    STACK_POP_E_STACK_ARG_NULL = 2,
    STACK_POP_E_OUT_ELEM_NULL = 2,
} ap_stack_pop_result;

ap_stack_pop_result ap_stack_pop(ap_stack_t *stack, void **element_out);

void ap_stack_destroy(ap_stack_t *stack);

#endif //STACK_LIB_H
