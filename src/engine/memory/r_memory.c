#include "r_memory.h"
#include "r_memory_block.c"
#include "plugins/plugin_a/plugin_a.h"
#include "plugins/plugin_a/plugin_a_api.h"
#include "plugins/plugin_b/plugin_b.h"
#include "plugins/plugin_b/plugin_b_api.h"

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

r_memory_block_t* //
r_memory_add_block(r_memory_t* memory, size_t size) {
  assert(size <= memory->capacity - memory->size);
  size_t total_block_size = sizeof(r_memory_block_t) + size;
  r_memory_block_t* block = (r_memory_block_t*)memory->current_addr;

  r_memory_block_init(block, memory->current_addr, total_block_size);
  r_memory_block_push_struct(block, r_memory_block_t);

  memory->current_addr = (u8*)memory->current_addr + total_block_size;
  memory->size += total_block_size;
  return block;
}

void //
r_memory_delete_block(r_memory_t* memory, r_memory_block_t* block) {
  assert(block->base_addr >= memory->base_addr);
  assert(block->base_addr < memory->current_addr);

  // note: (filipe.scur) we have to do a bit of pointer magic here :(
  // subtract block size to be deleted from all addresses to the right

  size_t block_size = block->size;
  r_memory_block_t* current = block->current_addr;
  
  while (current->base_addr) {
    current->base_addr = (u8*)current->base_addr - block_size;
    current->current_addr = (u8*)current->current_addr - block_size;
    current = (r_memory_block_t*)((u8*)current + current->size);
    // todo: (filipe.scur) assert we didnt go out of bounds
  }

  // note: (filipe.scur) now, the good thing is we can move the memory to the right all at once!
  r_memory_move(block->base_addr, block->current_addr, block_size);
  memory->current_addr = (u8*)memory->current_addr - block_size;
  memory->size -= block_size;
}