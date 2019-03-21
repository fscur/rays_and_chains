#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define PLUGIN_B_NAME = "plugin_b";

typedef struct r_plugin_manager_t r_plugin_manager_t;
typedef struct r_plugin_manager_api_t r_plugin_manager_api_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_memory_t r_memory_t;
typedef struct plugin_a_api_t plugin_a_api_t;

typedef void* (*R_PLUGIN_LOADER_FN)(void*, const char*);
typedef r_plugin_t* (*R_PLUGIN_MANAGER_FIND_PLUGIN)(r_plugin_manager_t*, const char*);

typedef struct plugin_b_t {
  plugin_a_api_t* plugin_a_api;
} plugin_b_t;

typedef void (*PRINTSUMFN)(plugin_b_t*, i32, i32);

typedef struct plugin_b_api_t {
  void* handle;
  void (*init)(plugin_b_t*, R_PLUGIN_MANAGER_FIND_PLUGIN, r_plugin_manager_t*);
  void (*render)(plugin_b_t*);
  void (*print_sum)(plugin_b_t*, i32, i32);
} plugin_b_api_t;

dll_export r_plugin_t* load_plugin_b(R_PLUGIN_LOADER_FN fn, r_memory_t* memory, void* handle);
dll_export void plugin_b_init(plugin_b_t* plugin_b, R_PLUGIN_MANAGER_FIND_PLUGIN find_plugin_fn, r_plugin_manager_t* plugin_manager);
dll_export void plugin_b_render(plugin_b_t* plugin_b);
dll_export void plugin_b_print_sum(plugin_b_t* plugin_b, i32 a, i32 b);

#ifdef __cplusplus
}
#endif