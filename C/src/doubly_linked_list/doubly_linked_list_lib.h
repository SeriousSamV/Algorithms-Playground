//
// Created by Samuel Vishesh Paul on 02/11/24.
//

#ifndef DOUBLY_LINKED_LIST_LIB_H
#define DOUBLY_LINKED_LIST_LIB_H

typedef struct dll_node {
    struct dll_node *next;
    struct dll_node *prev;
    void *data;
} dll_node;

dll_node *dll_new_node(const void *data);

void dll_set_data(dll_node *node, const void *data);

dll_node *dll_insert_after_node(dll_node *node, const void *data);

dll_node *dll_insert_before_node(dll_node *node, const void *data);

void dll_destroy(dll_node *node);

#endif //DOUBLY_LINKED_LIST_LIB_H
