#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_plugin_manager_t r_plugin_manager_t;

typedef struct r_plugin_t {
  void* handle;
  void (*init)(void* state, r_plugin_manager_t* plugin_manager);
  void (*update)(void* state, double dt);
  void* api;
  char* name;
  char* file_name;
  char* version;
  void* state_addr;
  size_t memory_size;
} r_plugin_t;

#ifdef __cplusplus
}
#endif