//
// Created by Samuel Vishesh Paul on 04/11/24.
//

#include <queue_lib.h>
#include <nullptr_fix.h>

#include <stdlib.h>

ap_queue_t * ap_queue_create(const size_t data_size) {
    ap_queue_t * queue = calloc(1, sizeof(queue));
    queue->data_size = data_size;
    return queue;
}

void ap_queue_enqueue(ap_queue_t *queue, const void *data) {
    if (queue->head == nullptr) {
        queue->head = ap_linked_list_create(data);
        queue->tail = queue->head;
        return;
    }
    queue->tail->next = ap_linked_list_create(data);
}

void * ap_queue_dequeue(ap_queue_t *queue) {
    if (queue->head == nullptr) {
        return nullptr;
    }
    const ap_linked_list_t * temp = queue->head;
    queue->head = queue->head->next;
    return temp->data;
}

void ap_queue_destroy(ap_queue_t *queue) {
    ap_linked_list_destroy(queue->head);
    free(queue);
}
