#include <stdlib.h>
#include <assert.h>

#include <linked_list_lib.h>

void test_int_linked_list() {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    ll_node *root = ll_node_new(&data[0]);
    for (int i = 1; i < sizeof(data) / sizeof(data[0]); i++) {
        ll_node_add(root, &data[i]);
    }

    const ll_node *current = root;
    int expected_data = 1;
    while (current != nullptr) {
        assert(*(int *)current->data == expected_data);
        expected_data++;
        current = current->next;
    }
    ll_destroy_node(root);
}

int main() {
    return EXIT_SUCCESS;
}
