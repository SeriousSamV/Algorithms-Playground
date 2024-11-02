#ifndef LINKED_LIST_LIB_H
#define LINKED_LIST_LIB_H

#include <nullptr_fix.h>

typedef struct ll_node {
    struct ll_node *next;
    void *data;
} ll_node;

ll_node *ll_node_new(const void *data);

ll_node *ll_node_get_next(const ll_node *node);

ll_node *ll_node_get_data(const ll_node *node);

void ll_node_add(ll_node *out_node, const void *data);

void ll_destroy_node(ll_node *node);

#endif //LINKED_LIST_LIB_H
