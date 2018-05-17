#include "r_memory.h"

void
arena_init(App_Memory_Arena* arena, void* base_addr) {
  arena->base_addr = base_addr;
  arena->current_addr = base_addr;
  arena->size = 0;
}

void*
arena_push(App_Memory_Arena* arena, size_t size) {
  void* ret = arena->current_addr;
  arena->size += size;
  arena->current_addr += size;
  return ret;
}