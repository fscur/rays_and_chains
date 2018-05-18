#pragma once
#include "r_types.h"
#include <stdlib.h>

typedef struct App_Memory {
  size_t permanent_size;
  u8* permanent_addr;
  size_t transient_size;
  u8* transient_addr;
} App_Memory;

typedef struct App_Memory_Arena {
  void* base_addr;
  void* current_addr;
  size_t size;
  size_t max_size;
} App_Memory_Arena;

#define arena_push_struct(arena_ptr, type)                                     \
  (type*)arena_push(arena_ptr, sizeof(type))

void arena_init(App_Memory_Arena* arena, void* base_addr, size_t max_size);
void* arena_push(App_Memory_Arena* arena, size_t size);