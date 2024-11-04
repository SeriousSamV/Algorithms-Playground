#ifndef QUEUE_LIB_H
#define QUEUE_LIB_H
#include <linked_list_lib.h>
#include <sys/types.h>

typedef struct ap_queue {
    ap_linked_list_t *head;
    ap_linked_list_t *tail;
    size_t size;
    size_t data_size;
} ap_queue_t;

ap_queue_t *ap_queue_create(size_t data_size);

void ap_queue_enqueue(ap_queue_t *queue, const void *data);

void *ap_queue_dequeue(ap_queue_t *queue);

void ap_queue_destroy(ap_queue_t *queue);

#endif //QUEUE_LIB_H
