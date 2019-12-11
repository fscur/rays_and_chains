#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_arena_t {
  void* base_addr;
  void* current_addr;
  size_t size;
  size_t max_size;
} r_memory_arena_t;

#define r_memory_arena_push_struct(arena_ptr, type)                                                \
  (type*)r_memory_arena_push(arena_ptr, sizeof(type))

#define r_memory_arena_push_array(arena_ptr, type, count)                                          \
  (type*)r_memory_arena_push(arena_ptr, sizeof(type) * count)

dll_export void //
r_memory_arena_init(r_memory_arena_t* arena, void* base_addr, size_t max_size);

dll_export void* //
r_memory_arena_push(r_memory_arena_t* arena, size_t size);

#ifdef __cplusplus
}
#endif