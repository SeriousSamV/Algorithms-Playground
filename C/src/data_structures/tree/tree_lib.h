#ifndef TREE_LIB_H
#define TREE_LIB_H

#include <stdbool.h>

typedef struct ap_tree_node {
    void *data;
    struct ap_tree_node *left;
    struct ap_tree_node *right;
} ap_tree_node_t;

typedef struct ap_tree {
    ap_tree_node_t *root;
    int (*comparator)(const void *lhs, const void *rhs);
    bool (*equals)(const void *lhs, const void *rhs);
} ap_tree_t;

ap_tree_t *ap_tree_node_create(
    void *data,
    int (*comparator_ptr)(const void *lhs, const void *rhs),
    bool (*equal_ptr)(const void *lhs, const void *rhs));

typedef enum ap_tree_insert_result {
    TREE_INSERT_OK = 0,
    TREE_INSERT_E_TREE_ARG_NULL = -1,
    TREE_INSERT_UNICORN_CASE = -69,
} ap_tree_insert_result;

ap_tree_insert_result ap_tree_insert(const ap_tree_t *tree, void *data);

ap_tree_t *ap_tree_delete(ap_tree_t *tree, void *data);

void ap_tree_destroy(ap_tree_t *tree);

void ap_tree_print(const ap_tree_t *tree);

#endif //TREE_LIB_H
