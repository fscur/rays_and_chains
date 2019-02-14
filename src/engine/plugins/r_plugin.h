#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"
typedef struct r_plugin_t {
  char* file_name;
  void* handle;
  void* state_addr;
  size_t memory_size;
} r_plugin_t;

#ifdef __cplusplus
}
#endif