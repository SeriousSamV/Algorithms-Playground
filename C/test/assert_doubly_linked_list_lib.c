#include <stdlib.h>
#include <assert.h>

#include <doubly_linked_list_lib.h>
#include <nullptr_fix.h>

void test_int_doubly_linked_list() {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    dll_node *root = dll_new_node(&data[0]);
    dll_node *curr = root;
    for (int i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        curr = dll_insert_after_node(curr, &data[i]);
    }

    curr = root;
    int expected_data = 1;
    while (curr != NULL) {
        assert(*(int *)curr->data == expected_data);
        expected_data++;
        curr = curr->next;
    }
    dll_destroy(root);
}

void test_int_dll_random_inserts() {
    const int data[] = {1, 2, 3, 4, 5};
    dll_node *root = dll_new_node(&data[2]); // 3
    dll_insert_before_node(root, &data[1]); // 2
    dll_insert_after_node(root, &data[3]); // 4
    dll_insert_after_node(root->next, &data[4]); // 5
    dll_insert_before_node(root->prev, &data[0]);

    dll_node const *curr = root->prev->prev;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        assert(*(int *) curr->data == data[i]);
        curr = curr->next;
    }

    dll_destroy(root);
}

void test_string_dll_random_inserts() {
    const char* data[] = {"one", "two", "three", "four", "five"};
    dll_node *root = dll_new_node(&data[2]); // 3
    dll_insert_before_node(root, &data[1]); // 2
    dll_insert_after_node(root, &data[3]); // 4
    dll_insert_after_node(root->next, &data[4]); // 5
    dll_insert_before_node(root->prev, &data[0]);

    dll_node const *curr = root->prev->prev;
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        assert(*(char **) curr->data == data[i]);
        curr = curr->next;
    }

    dll_destroy(root);
}

int main() {
    test_int_doubly_linked_list();
    test_int_dll_random_inserts();
    test_string_dll_random_inserts();

    return EXIT_SUCCESS;
}
