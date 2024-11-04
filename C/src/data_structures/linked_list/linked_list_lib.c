//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#include "linked_list_lib.h"
#include <nullptr_fix.h>

#include <stdlib.h>

ap_linked_list_t *ap_linked_list_create(const void *data) {
    ap_linked_list_t *new_node = calloc(1, sizeof(ap_linked_list_t));
    new_node->data = (void *) data;
    new_node->next = nullptr;
    return new_node;
}

ap_linked_list_t *ap_linked_list_get_next(const ap_linked_list_t *node) {
    return node->next;
}

ap_linked_list_t *ap_linked_list_get_data(const ap_linked_list_t *node) {
    return node->data;
}

ap_linked_list_t* ap_linked_list_add_node(ap_linked_list_t *out_node, const void *data) {
    ap_linked_list_t *new_node = ap_linked_list_create(data);
    out_node->next = new_node;
    return new_node;
}


void ap_linked_list_destroy(ap_linked_list_t *node) {
    ap_linked_list_t *curr = node;
    while (curr != nullptr) {
        ap_linked_list_t *next = ap_linked_list_get_next(curr);
        free(curr);
        curr = next;
    }
}
