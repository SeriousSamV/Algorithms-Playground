//
// Created by Samuel Vishesh Paul on 04/11/24.
//

#include <queue_lib.h>
#include <nullptr_fix.h>

#include <stdlib.h>

queue * queue_create(const size_t data_size) {
    queue * queue = calloc(1, sizeof(queue));
    queue->data_size = data_size;
    return queue;
}

void queue_enqueue(queue *queue, const void *data) {
    if (queue->head == nullptr) {
        queue->head = ll_node_new(data);
        queue->tail = queue->head;
        return;
    }
    queue->tail->next = ll_node_new(data);
}

void * queue_dequeue(queue *queue) {
    if (queue->head == nullptr) {
        return nullptr;
    }
    const ll_node * temp = queue->head;
    queue->head = queue->head->next;
    return temp->data;
}

void queue_destroy(queue *queue) {
    ll_destroy(queue->head);
    free(queue);
}
