//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#include "linked_list_lib.h"

#include <stdlib.h>

ll_node *ll_node_new(const void *data) {
    ll_node *new_node = calloc(1, sizeof(ll_node));
    new_node->data = (void *) data;
    new_node->next = nullptr;
    return new_node;
}

ll_node *ll_node_get_next(const ll_node *node) {
    return node->next;
}

ll_node *ll_node_get_data(const ll_node *node) {
    return node->data;
}

void ll_node_add(ll_node *out_node, const void *data) {
    ll_node *new_node = ll_node_new(data);
    out_node->next = new_node;
}


void ll_destroy_node(ll_node *node) {
    ll_node *curr = node;
    while (curr != nullptr) {
        ll_node *next = ll_node_get_next(curr);
        free(curr);
        curr = next;
    }
}
