#include "r_linked_list.h"

r_linked_list_t* //
r_linked_list_new() {
  return calloc(1, sizeof(r_linked_list_t));
}

void //
r_linked_list_free(r_linked_list_t* list) {
  r_linked_list_node_t* current = list->head;

  while (current != NULL) {
    r_linked_list_node_t* next = current->next;
    free(current);
    current = next;
  }

  free(list);
}

void //
r_linked_list_insert(r_linked_list_t* list, r_linked_list_node_t* node) {
  r_linked_list_node_t* current = list->head;
  node->next = current;
  list->head = node;

  if (list->tail == NULL)
    list->tail = node;
}

void //
r_linked_list_push_back(r_linked_list_t* list, r_linked_list_node_t* node) {
  if (list->tail == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}