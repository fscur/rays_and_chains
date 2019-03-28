#include "r_memory_block.h"

void
r_memory_block_init(r_memory_block_t* block, void* base_addr, size_t max_size) {
  assert(max_size > 0);
  assert(base_addr != NULL);
  block->base_addr = base_addr;
  block->current_addr = base_addr;
  block->size = 0;
  block->max_size = max_size;
}

void*
r_memory_block_push(r_memory_block_t* block, size_t size) {
  assert(block->size + size <= block->max_size);
  void* ret = block->current_addr;
  block->size += size;
  block->current_addr = (u8*)block->current_addr + size;
  return ret;
}