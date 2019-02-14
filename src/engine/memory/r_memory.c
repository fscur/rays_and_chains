#include "r_memory.h"

r_memory_t
r_memory_create(size_t permanent_size, size_t transient_size) {

#if _DEBUG
  void* base_addr = (void*)terabytes(1);
#else
  void* base_addr = NULL;
#endif

  r_memory_t memory;
  memory.permanent_size = permanent_size;
  memory.transient_size = transient_size;

  u64 total_memory_size = memory.permanent_size + memory.transient_size;

  memory.permanent_addr = r_memory_virtual_alloc(base_addr, total_memory_size);
  memory.transient_addr = (void*)(memory.permanent_addr + memory.permanent_size);

  assert(memory.permanent_addr != NULL);

  return memory;
}