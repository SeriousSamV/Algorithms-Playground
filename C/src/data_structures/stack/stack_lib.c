//
// Created by Samuel Vishesh Paul on 03/11/24.
//

#include <stack_lib.h>
#include <stdlib.h>


stack *stack_create(const size_t initial_capacity, const size_t element_size) {
    stack *stack = calloc(1, sizeof(struct stack));
    stack->storage = vector_create(initial_capacity, element_size);
    stack->top_index = 0;
    return stack;
}

stack_push_result stack_push(stack *stack, const void *element) {
    if (stack == nullptr) {
        return STACK_PUSH_E_STACK_ARG_NULL;
    }
    const vector_append_elem_result res =
            vector_append_elem(stack->storage, element);
    if (res != VECTOR_APPEND_OK) {
        return STACK_PUSH_E_STORAGE;
    }
    stack->top_index++;
    return STACK_PUSH_OK;
}

stack_pop_result stack_pop(stack *stack, void **element_out) {
    if (stack == nullptr) {
        return STACK_POP_E_STACK_ARG_NULL;
    }
    if (element_out == nullptr) {
        return STACK_POP_E_OUT_ELEM_NULL;
    }
    if (stack->top_index <= 0) {
        return STACK_POP_E_EMPTY;
    }
    *element_out = vector_get_elem_at(stack->storage, stack->top_index - 1);
    stack->top_index--;
    return STACK_POP_OK;
}

void stack_destroy(stack *stack) {
    if (stack == nullptr) {
        return;
    }
    vector_destroy(stack->storage);
    free(stack);
}
