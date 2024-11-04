//
// Created by Samuel Vishesh Paul on 03/11/24.
//

#include <stack_lib.h>
#include <stdlib.h>
#include <nullptr_fix.h>

ap_stack_t *ap_stack_create(const size_t initial_capacity, const size_t element_size) {
    ap_stack_t *stack = calloc(1, sizeof(struct ap_stack));
    stack->storage = ap_vector_create(initial_capacity, element_size);
    stack->top_index = 0;
    return stack;
}

ap_stack_push_result ap_stack_push(ap_stack_t *stack, const void *element) {
    if (stack == nullptr) {
        return STACK_PUSH_E_STACK_ARG_NULL;
    }
    const ap_vector_append_elem_result res =
            ap_vector_append_elem(stack->storage, element);
    if (res != VECTOR_APPEND_OK) {
        return STACK_PUSH_E_STORAGE;
    }
    stack->top_index++;
    return STACK_PUSH_OK;
}

ap_stack_pop_result ap_stack_pop(ap_stack_t *stack, void **element_out) {
    if (stack == nullptr) {
        return STACK_POP_E_STACK_ARG_NULL;
    }
    if (element_out == nullptr) {
        return STACK_POP_E_OUT_ELEM_NULL;
    }
    if (stack->top_index <= 0) {
        return STACK_POP_E_EMPTY;
    }
    *element_out = ap_vector_get_elem_at(stack->storage, stack->top_index - 1);
    stack->top_index--;
    return STACK_POP_OK;
}

void ap_stack_destroy(ap_stack_t *stack) {
    if (stack == nullptr) {
        return;
    }
    ap_vector_destroy(stack->storage);
    free(stack);
}
