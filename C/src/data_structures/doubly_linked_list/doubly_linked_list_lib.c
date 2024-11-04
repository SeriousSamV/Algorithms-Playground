//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#include <doubly_linked_list_lib.h>
#include <nullptr_fix.h>

#include <stdlib.h>

ap_doubly_linked_list_t *ap_doubly_linked_list_create(const void *data) {
    ap_doubly_linked_list_t *new_node = calloc(1, sizeof(ap_doubly_linked_list_t));
    new_node->data = (void *) data;
    new_node->next = nullptr;
    return new_node;
}

void ap_doubly_linked_list_set_data(ap_doubly_linked_list_t *node, const void *data) {
    node->data = (void *) data;
}

ap_doubly_linked_list_t *ap_doubly_linked_list_insert_after(ap_doubly_linked_list_t *node, const void *data) {
    if (node == nullptr) {
        return ap_doubly_linked_list_create(data);
    }
    ap_doubly_linked_list_t *new_node = ap_doubly_linked_list_create(data);
    ap_doubly_linked_list_t *old_next = node->next;
    if (old_next != nullptr) {
        old_next->prev = new_node;
    }
    new_node->next = old_next;
    new_node->prev = node;
    node->next = new_node;
    return new_node;
}

ap_doubly_linked_list_t *ap_doubly_linked_list_insert_before(ap_doubly_linked_list_t *node, const void *data) {
    if (node == nullptr) {
        return ap_doubly_linked_list_create(data);
    }
    ap_doubly_linked_list_t *new_node = ap_doubly_linked_list_create(data);
    ap_doubly_linked_list_t *old_prev = node->prev;
    if (old_prev != nullptr) {
        old_prev->next = new_node;
    }
    new_node->prev = old_prev;
    new_node->next = node;
    node->prev = new_node;
    return new_node;
}

void ap_doubly_linked_list_destroy(ap_doubly_linked_list_t *node) {
    if (node == nullptr) {
        return;
    }
    ap_doubly_linked_list_t *curr = node->prev;
    while (curr != nullptr) {
        ap_doubly_linked_list_t *prev = curr->prev;
        free(curr);
        curr = prev;
    }
    curr = node->next;
    while (curr != nullptr) {
        ap_doubly_linked_list_t *next = curr->next;
        free(curr);
        curr = next;
    }
    free(node);
}
