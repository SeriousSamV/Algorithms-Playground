#ifndef LINKED_LIST_LIB_H
#define LINKED_LIST_LIB_H

typedef struct ap_linked_list {
    struct ap_linked_list *next;
    void *data;
} ap_linked_list_t;

ap_linked_list_t *ap_linked_list_create(const void *data);

ap_linked_list_t *ap_linked_list_get_next(const ap_linked_list_t *node);

ap_linked_list_t *ap_linked_list_get_data(const ap_linked_list_t *node);

ap_linked_list_t *ap_linked_list_add_node(ap_linked_list_t *out_node, const void *data);

void ap_linked_list_destroy(ap_linked_list_t *node);

#endif //LINKED_LIST_LIB_H
