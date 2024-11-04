//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#ifndef DOUBLY_LINKED_LIST_LIB_H
#define DOUBLY_LINKED_LIST_LIB_H

typedef struct ap_doubly_linked_list {
    struct ap_doubly_linked_list *next;
    struct ap_doubly_linked_list *prev;
    void *data;
} ap_doubly_linked_list_t;

ap_doubly_linked_list_t *ap_doubly_linked_list_create(const void *data);

void ap_doubly_linked_list_set_data(ap_doubly_linked_list_t *node, const void *data);

ap_doubly_linked_list_t *ap_doubly_linked_list_insert_after(ap_doubly_linked_list_t *node, const void *data);

ap_doubly_linked_list_t *ap_doubly_linked_list_insert_before(ap_doubly_linked_list_t *node, const void *data);

void ap_doubly_linked_list_destroy(ap_doubly_linked_list_t *node);

#endif //DOUBLY_LINKED_LIST_LIB_H
