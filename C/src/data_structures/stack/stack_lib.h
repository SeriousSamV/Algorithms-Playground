#ifndef STACK_LIB_H
#define STACK_LIB_H

#include <vector_lib.h>

typedef struct stack {
    vector *storage;
    size_t top_index;
} stack;

stack *stack_create(const size_t initial_capacity, const size_t element_size);

typedef enum stack_push_result {
    STACK_PUSH_OK = 0,
    STACK_PUSH_E_STACK_ARG_NULL = 1,
    STACK_PUSH_E_STORAGE = 2,
} stack_push_result;

stack_push_result stack_push(stack *stack, const void *element);

typedef enum stack_pop_result {
    STACK_POP_OK = 0,
    STACK_POP_E_EMPTY = 1,
    STACK_POP_E_STACK_ARG_NULL = 2,
    STACK_POP_E_OUT_ELEM_NULL = 2,
} stack_pop_result;

stack_pop_result stack_pop(stack *stack, void **element_out);

void stack_destroy(stack *stack);

#endif //STACK_LIB_H
