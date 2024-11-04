#ifndef QUEUE_LIB_H
#define QUEUE_LIB_H
#include <linked_list_lib.h>
#include <sys/types.h>

typedef struct queue {
    ll_node *head;
    ll_node *tail;
    size_t size;
    size_t data_size;
} queue;

queue *queue_create(size_t data_size);

void queue_enqueue(queue *queue, const void *data);

void *queue_dequeue(queue *queue);

void queue_destroy(queue *queue);

#endif //QUEUE_LIB_H
