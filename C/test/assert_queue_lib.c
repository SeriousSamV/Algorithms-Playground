#include <stdlib.h>
#include <assert.h>
#include <nullptr_fix.h>
#include <queue_lib.h>

void test_queue() {
    queue *queue = queue_create(sizeof(int));
    const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        queue_enqueue(queue, &arr[i]);
    }
    for (int i = sizeof(arr) / sizeof(arr[0]); i >= 0; i--) {
        const int val = *((int *) queue_dequeue(queue));
        assert(val == arr[i]);
    }
    queue_destroy(queue);
}

int main() {
    return EXIT_SUCCESS;
}
