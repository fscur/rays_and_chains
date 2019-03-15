#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_MAX_MEMORY_USAGE gigabytes(2)

typedef struct r_memory_arena_t r_memory_arena_t;

typedef struct r_memory_t {
  void* base_addr;
  void* current_addr;
  size_t size;
  size_t capacity;
} r_memory_t;

dll_export r_memory_t //
r_memory_create(size_t capacity);

dll_export r_memory_arena_t* //
r_memory_add_arena(r_memory_t* memory, size_t arena_size);

u8* //
r_memory_virtual_alloc(void* base_addr, size_t size);

#ifdef __cplusplus
}
#endif