#include <stdlib.h>
#include <assert.h>

#include <linked_list_lib.h>
#include <nullptr_fix.h>
#include <string.h>

void test_int_linked_list() {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ap_linked_list_t *root = ap_linked_list_create(&data[0]);
    ap_linked_list_t *curr = root;
    for (size_t i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        curr = ap_linked_list_add_node(curr, &data[i]);
    }

    const ap_linked_list_t *current = root;
    int expected_data = 1;
    while (current != NULL) {
        assert(*(int *)current->data == expected_data);
        expected_data++;
        current = current->next;
    }
    ap_linked_list_destroy(root);
}

void test_string_linked_list() {
    const char *data[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
    ap_linked_list_t *root = ap_linked_list_create(data[0]);
    ap_linked_list_t *curr = root;
    for (size_t i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        curr = ap_linked_list_add_node(curr, data[i]);
    }

    const ap_linked_list_t *current = root;
    int expected_index = 0;
    while (current != NULL) {
        assert(strcmp(current->data, data[expected_index]) == 0);
        expected_index++;
        current = current->next;
    }
    ap_linked_list_destroy(root);
}

int main() {
    test_int_linked_list();
    test_string_linked_list();

    return EXIT_SUCCESS;
}
