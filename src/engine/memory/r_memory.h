#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_memory_t {
  size_t permanent_size;
  u8* permanent_addr;
  size_t transient_size;
  u8* transient_addr;
} r_memory_t;

typedef struct r_memory_api {
  void* handle;
  r_memory_t (*create)(size_t, size_t);
} r_memory_api;

typedef r_memory_t (*R_MEMORY_CREATE)(size_t, size_t);

dll_export r_memory_t //
r_memory_create(size_t permanent_size, size_t transient_size);

u8* //
r_memory_virtual_alloc(void* base_addr, size_t size);

#ifdef __cplusplus
}
#endif