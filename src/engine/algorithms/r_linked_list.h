#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_linked_list_node_t {
  int data;
  struct r_linked_list_node_t* next;
} r_linked_list_node_t;

typedef struct r_linked_list_t {
  struct r_linked_list_node_t* head;
  struct r_linked_list_node_t* tail;
} r_linked_list_t;

dll_export r_linked_list_t* //
r_linked_list_new();

dll_export void //
r_linked_list_free(r_linked_list_t* list);

dll_export void //
r_linked_list_insert(r_linked_list_t* list, r_linked_list_node_t* node);

dll_export void //
r_linked_list_push_back(r_linked_list_t* list, r_linked_list_node_t* node);

#ifdef __cplusplus
}
#endif