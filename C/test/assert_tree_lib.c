#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <tree_lib.h>

int compare_ints(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);
    return *(int *)a - *(int *)b;
}

bool is_equal_ints(const void *a, const void *b) {
    assert(a != nullptr);
    assert(b != nullptr);
    return *(int *)a == *(int *)b;
}

void test_tree_lib() {
    int a = 5;
    ap_tree *tree = tree_node_create(&a, &compare_ints, &is_equal_ints);
    assert(tree->root != nullptr);
    assert(*(int*)tree->root->data == 5);
    int b = 6;
    const tree_insert_result r1 = tree_insert(tree, &b);
    assert(r1 == TREE_INSERT_OK);
    assert(tree->root != nullptr);
    assert(*(int*)tree->root->data == 5);
    assert(tree->root->left == nullptr);
    assert(tree->root->right != nullptr);
    assert(*(int*)tree->root->right->data == 6);
    int c = 4;
    const tree_insert_result r2 = tree_insert(tree, &c);
    assert(r2 == TREE_INSERT_OK);
    assert(tree->root != nullptr);
    assert(*(int*)tree->root->data == 5);
    assert(tree->root->left != nullptr);
    assert(tree->root->right != nullptr);
    assert(*(int*)tree->root->right->data == 6);
    assert(*(int*)tree->root->left->data == 4);
    int d = 2;
    const tree_insert_result r3 = tree_insert(tree, &d);
    assert(r3 == TREE_INSERT_OK);
    assert(tree->root != nullptr);
    assert(*(int*)tree->root->data == 5);
    assert(tree->root->left != nullptr);
    assert(tree->root->right != nullptr);
    assert(*(int*)tree->root->right->data == 6);
    assert(*(int*)tree->root->left->data == 4);
    assert(tree->root->left->left != nullptr);
    assert(*(int *) tree->root->left->left->data == 2);
    int e = 10;
    const tree_insert_result r4 = tree_insert(tree, &e);
    assert(r4 == TREE_INSERT_OK);
    assert(tree->root != nullptr);
    assert(*(int*)tree->root->data == 5);
    assert(tree->root->left != nullptr);
    assert(tree->root->right != nullptr);
    assert(*(int*)tree->root->right->data == 6);
    assert(*(int*)tree->root->left->data == 4);
    assert(tree->root->left->left != nullptr);
    assert(*(int *) tree->root->left->left->data == 2);
    assert(tree->root->right->right != nullptr);
    assert(*(int*)tree->root->right->right->data == 10);

    tree_print(tree);
    tree_destroy(tree);
}

int main() {
    test_tree_lib();

    return EXIT_SUCCESS;
}
