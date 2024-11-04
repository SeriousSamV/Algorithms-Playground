#include <tree_lib.h>
#include <nullptr_fix.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ap_tree * tree_node_create(
    void *data,
    int(*comparator_ptr)(const void *lhs, const void *rhs),
    bool(*equal_ptr)(const void *lhs, const void *rhs)) {
    ap_tree *tree = calloc(1, sizeof(ap_tree));
    tree->root = calloc(1, sizeof(struct tree_node));
    tree->root->data = data;
    tree->comparator = comparator_ptr;
    tree->equals = equal_ptr;
    return tree;
}

tree_insert_result tree_insert(const ap_tree *tree, void *data) {
    if (tree == nullptr) {
        fprintf(stderr, "tree root is null\n");
        fflush(stderr);
        return TREE_INSERT_E_TREE_ARG_NULL;
    }
    tree_node_t *cur = tree->root;
    tree_node_t *future = tree->root;
    bool isRight = false;
    while (future != nullptr) {
        cur = future;
        if (tree->comparator(data, future->data) > 0) {
            future = future->right;
            isRight = true;
        } else {
            future = future->left;
            isRight = false;
        }
    }

    if (isRight) {
        cur->right = calloc(1, sizeof(struct tree_node));
        cur->right->data = data;
    } else {
        cur->left = calloc(1, sizeof(struct tree_node));
        cur->left->data = data;
    }

    return TREE_INSERT_OK;
}
