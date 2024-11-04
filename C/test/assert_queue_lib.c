#include <stdlib.h>
#include <assert.h>
#include <nullptr_fix.h>
#include <queue_lib.h>

void test_queue() {
    ap_queue_t *queue = ap_queue_create(sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        ap_queue_enqueue(queue, &arr[i]);
    }
    for (size_t i = sizeof(arr) / sizeof(arr[0]); i >= 0; i--) {
        const int val = *((int *) ap_queue_dequeue(queue));
        assert(val == arr[i]);
    }
    ap_queue_destroy(queue);
}

int main() {
    return EXIT_SUCCESS;
}
