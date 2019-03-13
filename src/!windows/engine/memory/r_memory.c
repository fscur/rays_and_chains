#include <windows.h>
#include <memoryapi.h>
#include "engine/memory/r_memory.c"

u8* //
r_memory_virtual_alloc(void* base_addr, size_t size) {
  return (u8*)VirtualAlloc(base_addr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}