#ifndef TREE_LIB_H
#define TREE_LIB_H

typedef struct tree_node {
    void *data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct ap_tree {
    tree_node_t *root;
    int (*comparator)(const void *lhs, const void *rhs);
    bool (*equals)(const void *lhs, const void *rhs);
} ap_tree;

ap_tree *tree_node_create(
    void *data,
    int (*comparator_ptr)(const void *lhs, const void *rhs),
    bool (*equal_ptr)(const void *lhs, const void *rhs));

typedef enum tree_insert_result {
    TREE_INSERT_OK = 0,
    TREE_INSERT_E_TREE_ARG_NULL = 1,
} tree_insert_result;

tree_insert_result tree_insert(const ap_tree *tree, void *data);

ap_tree *tree_delete(ap_tree *tree, void *data);

void tree_destroy(ap_tree *tree);

void tree_print(ap_tree *tree);

#endif //TREE_LIB_H
