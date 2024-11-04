#include <stdlib.h>
#include <assert.h>

#include <doubly_linked_list_lib.h>
#include <nullptr_fix.h>

void test_int_doubly_linked_list() {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ap_doubly_linked_list_t *root = ap_doubly_linked_list_create(&data[0]);
    ap_doubly_linked_list_t *curr = root;
    for (size_t i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        curr = ap_doubly_linked_list_insert_after(curr, &data[i]);
    }

    curr = root;
    int expected_data = 1;
    while (curr != NULL) {
        assert(*(int *)curr->data == expected_data);
        expected_data++;
        curr = curr->next;
    }
    ap_doubly_linked_list_destroy(root);
}

void test_int_dll_random_inserts() {
    const int data[] = {1, 2, 3, 4, 5};
    ap_doubly_linked_list_t *root = ap_doubly_linked_list_create(&data[2]); // 3
    ap_doubly_linked_list_insert_before(root, &data[1]); // 2
    ap_doubly_linked_list_insert_after(root, &data[3]); // 4
    ap_doubly_linked_list_insert_after(root->next, &data[4]); // 5
    ap_doubly_linked_list_insert_before(root->prev, &data[0]);

    ap_doubly_linked_list_t const *curr = root->prev->prev;
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        assert(*(int *) curr->data == data[i]);
        curr = curr->next;
    }

    ap_doubly_linked_list_destroy(root);
}

void test_string_dll_random_inserts() {
    const char* data[] = {"one", "two", "three", "four", "five"};
    ap_doubly_linked_list_t *root = ap_doubly_linked_list_create(&data[2]); // 3
    ap_doubly_linked_list_insert_before(root, &data[1]); // 2
    ap_doubly_linked_list_insert_after(root, &data[3]); // 4
    ap_doubly_linked_list_insert_after(root->next, &data[4]); // 5
    ap_doubly_linked_list_insert_before(root->prev, &data[0]);

    ap_doubly_linked_list_t const *curr = root->prev->prev;
    for (size_t i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        assert(*(char **) curr->data == data[i]);
        curr = curr->next;
    }

    ap_doubly_linked_list_destroy(root);
}

int main() {
    test_int_doubly_linked_list();
    test_int_dll_random_inserts();
    test_string_dll_random_inserts();

    return EXIT_SUCCESS;
}
