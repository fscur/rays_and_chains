#include "r_memory_arena.h"

void
r_memory_arena_init(r_memory_arena_t* arena, void* base_addr, size_t max_size) {
  assert(max_size > 0);
  assert(base_addr != NULL);
  arena->base_addr = base_addr;
  arena->current_addr = base_addr;
  arena->size = 0;
  arena->max_size = max_size;
}

void*
r_memory_arena_push(r_memory_arena_t* arena, size_t size) {
  assert(arena->size + size <= arena->max_size);
  void* ret = arena->current_addr;
  arena->size += size;
  arena->current_addr = (char*)arena->current_addr + size;
  return ret;
}