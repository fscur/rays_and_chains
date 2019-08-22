#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_MAX_MEMORY_USAGE gigabytes(2)

typedef struct r_memory_block_t r_memory_block_t;

typedef struct r_memory_t {
  void* base_addr;
  void* current_addr;
  size_t size;
  size_t capacity;
} r_memory_t;

dll_export r_memory_t //
r_memory_create(size_t capacity);

dll_export r_memory_block_t* //
r_memory_add_block(r_memory_t* memory, size_t block_size);

dll_export void //
r_memory_delete_block(r_memory_t* memory, r_memory_block_t* block);

u8* //
r_memory_virtual_alloc(void* base_addr, size_t size);

void //
r_memory_move(void* dest, void* src, size_t size);

#ifdef __cplusplus
}
#endif