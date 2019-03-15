#include "r_memory.h"
#include "r_memory_arena.c"

r_memory_t
r_memory_create(size_t capacity) {
  
assert(capacity < R_MAX_MEMORY_USAGE);

#if _DEBUG
  void* base_addr = (void*)terabytes(1);
#else
  void* base_addr = NULL;
#endif

  r_memory_t memory = {0};
  memory.capacity = capacity;
  memory.base_addr = r_memory_virtual_alloc(base_addr, capacity);
  assert(memory.base_addr != NULL);

  memory.current_addr = memory.base_addr;
  return memory;
}

r_memory_arena_t* //
r_memory_add_arena(r_memory_t* memory, size_t size) {
  assert(size <= memory->capacity - memory->size);
  size_t total_arena_size = sizeof(r_memory_arena_t) + size;
  r_memory_arena_t* arena = (r_memory_arena_t*)memory->current_addr;

  r_memory_arena_init(arena, memory->current_addr, total_arena_size);
  R_MEMORY_ARENA_PUSH_STRUCT(arena, r_memory_arena_t);

  memory->current_addr = (u8*)memory->current_addr + total_arena_size;
  memory->size += total_arena_size;
  return arena;
}