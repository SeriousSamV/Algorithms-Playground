#include <stdlib.h>
#include <assert.h>
#include <nullptr_fix.h>
#include <stack_lib.h>


void test_stack_push_and_pop() {
    stack *stack = stack_create(5, sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        assert(stack->top_index == i);
        const stack_push_result push_res = stack_push(stack, &arr[i]);
        assert(push_res == STACK_PUSH_OK);
        assert(stack->top_index == i + 1);
    }
    for (size_t i = sizeof(arr) / sizeof(arr[0]) - 1; i >= 0; i--) {
        assert(stack->top_index == i + 1);
        int *top_val = nullptr;
        const stack_pop_result pop_res = stack_pop(stack, (void **) &top_val);
        assert(pop_res == STACK_POP_OK);
        assert(*top_val == arr[i]);
        assert(stack->top_index == i);
    }
    stack_destroy(stack);
}

int main() {
    test_stack_push_and_pop();

    return EXIT_SUCCESS;
}
