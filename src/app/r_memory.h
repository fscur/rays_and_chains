#pragma once
#include "r_types.h"
#include <stdlib.h>

typedef struct App_Memory {
  u64 permanent_size;
  u8* permanent_addr;
  u64 transient_size;
  u8* transient_addr;
} App_Memory;

typedef struct App_Memory_Arena {
  void* base_addr;
  void* current_addr;
  size_t size;
} App_Memory_Arena;

#define arena_push_struct(arena_ptr, type)                                     \
  (type*)arena_push(arena_ptr, sizeof(type))

void arena_init(App_Memory_Arena* arena, void* base_addr);
void* arena_push(App_Memory_Arena* arena, size_t size);