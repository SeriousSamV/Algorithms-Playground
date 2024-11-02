//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#include <doubly_linked_list_lib.h>
#include <nullptr_fix.h>

#include <stdlib.h>

dll_node *dll_new_node(const void *data) {
    dll_node *new_node = calloc(1, sizeof(dll_node));
    new_node->data = (void *) data;
    new_node->next = nullptr;
    return new_node;
}

void dll_set_data(dll_node *node, const void *data) {
    node->data = (void *) data;
}

dll_node *dll_insert_after_node(dll_node *node, const void *data) {
    if (node == nullptr) {
        return dll_new_node(data);
    }
    dll_node *new_node = dll_new_node(data);
    dll_node *old_next = node->next;
    if (old_next != nullptr) {
        old_next->prev = new_node;
    }
    new_node->next = old_next;
    new_node->prev = node;
    node->next = new_node;
    return new_node;
}

dll_node *dll_insert_before_node(dll_node *node, const void *data) {
    if (node == nullptr) {
        return dll_new_node(data);
    }
    dll_node *new_node = dll_new_node(data);
    dll_node *old_prev = node->prev;
    if (old_prev != nullptr) {
        old_prev->next = new_node;
    }
    new_node->prev = old_prev;
    new_node->next = node;
    node->prev = new_node;
    return new_node;
}

void dll_destroy(dll_node *node) {
    if (node == nullptr) {
        return;
    }
    dll_node *curr = node->prev;
    while (curr != nullptr) {
        dll_node *prev = curr->prev;
        free(curr);
        curr = prev;
    }
    curr = node->next;
    while (curr != nullptr) {
        dll_node *next = curr->next;
        free(curr);
        curr = next;
    }
    free(node);
}
