#include <tree_lib.h>
#include <nullptr_fix.h>
#include <stdio.h>
#include <stdlib.h>
// ReSharper disable once CppUnusedIncludeDirective
#include <stdbool.h>

ap_tree_t * ap_tree_node_create(
    void *data,
    int(*comparator_ptr)(const void *lhs, const void *rhs),
    bool(*equal_ptr)(const void *lhs, const void *rhs)) {
    ap_tree_t *tree = calloc(1, sizeof(ap_tree_t));
    tree->root = calloc(1, sizeof(struct ap_tree_node));
    tree->root->data = data;
    tree->comparator = comparator_ptr;
    tree->equals = equal_ptr;
    return tree;
}

ap_tree_insert_result ap_tree_insert(const ap_tree_t *tree, void *data) {
    if (tree == nullptr) {
        fprintf(stderr, "tree root is null\n");
        fflush(stderr);
        return TREE_INSERT_E_TREE_ARG_NULL;
    }
    ap_tree_node_t *future = tree->root;
    while (future != nullptr) {
        if (tree->comparator(data, future->data) > 0) {
            if (future->right == nullptr) {
                future->right = calloc(1, sizeof(struct ap_tree_node));
                future->right->data = data;
                return TREE_INSERT_OK;
            }
            future = future->right;
        } else {
            if (future->left == nullptr) {
                future->left = calloc(1, sizeof(struct ap_tree_node));
                future->left->data = data;
                return TREE_INSERT_OK;
            }
            future = future->left;
        }
    }
    return TREE_INSERT_UNICORN_CASE;
}

void tree_node_print_indent(const ap_tree_node_t *node, const int depth) { // NOLINT(*-no-recursion)
    if (node == nullptr) {
        for (int i = 0; i < depth; ++i) {
            printf("\t");
        }
        printf("NULL\n");
        return;
    }

    tree_node_print_indent(node->right, depth + 1);

    for (int i = 0; i < depth; ++i) {
        printf("\t");
    }
    printf("%d\n", *(int *) node->data);

    tree_node_print_indent(node->left, depth + 1);
}

void tree_node_destroy(ap_tree_node_t *node) { // NOLINT(*-no-recursion)
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        tree_node_destroy(node->left);
    }
    if (node->right != nullptr) {
        tree_node_destroy(node->right);
    }
    free(node);
}

void ap_tree_destroy(ap_tree_t *tree) {
    tree_node_destroy(tree->root);
    free(tree);
}

void ap_tree_print(const ap_tree_t *tree) {
    tree_node_print_indent(tree->root, 0);
}
