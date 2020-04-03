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
  r_memory_arena_push_struct(arena, r_memory_arena_t);

  memory->current_addr = (u8*)memory->current_addr + total_arena_size;
  memory->size += total_arena_size;
  return arena;
}

void //
r_memory_delete_arena(r_memory_t* memory, r_memory_arena_t* arena) {
  assert(arena->base_addr >= memory->base_addr);
  assert(arena->base_addr < memory->current_addr);

  // note: filipe.scur@gmail.com
  // we have to do a bit of pointer magic here :(
  // subtract arena size to be deleted from all addresses to the right

  size_t arena_size = arena->size;
  r_memory_arena_t* current = arena->current_addr;

  while (current->base_addr) {
    current->base_addr = (u8*)current->base_addr - arena_size;
    current->current_addr = (u8*)current->current_addr - arena_size;
    current = (r_memory_arena_t*)((u8*)current + current->size);
    // todo: filipe.scur@gmail.com
    // assert we didnt go out of bounds
  }

  // note: filipe.scur@gmail.com
  // now, the good thing is we can move the memory to the right all at once!
  size_t move_size = (u8*)memory->current_addr - (u8*)arena->current_addr;
  r_memory_move(arena->base_addr, arena->current_addr, move_size);
  memory->current_addr = (u8*)memory->current_addr - arena_size;
  memory->size -= arena_size;
}