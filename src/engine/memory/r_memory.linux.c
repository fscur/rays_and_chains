#include "engine/memory/r_memory.c"
#include <sys/mman.h>

u8* //
r_memory_virtual_alloc(void* base_addr, size_t size) {
  u8* result_addr = (u8*) mmap(base_addr, size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);  
  u32 result = mprotect(result_addr, size, PROT_READ | PROT_WRITE);
  assert(result == 0);
  return result_addr;  
}

void //
r_memory_move(void* dest, void* src, size_t size) {
  memmove(dest, src, size);
}