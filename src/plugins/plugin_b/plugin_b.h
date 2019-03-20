#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"


#define PLUGIN_B_NAME = "plugin_b";

typedef struct r_plugin_manager_t r_plugin_manager_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_memory_t r_memory_t;
typedef struct plugin_a_api_t plugin_a_api_t;

typedef struct plugin_b_t {
  plugin_a_api_t* plugin_a_api;
} plugin_b_t;

typedef void (*PLBINITFN)(plugin_b_t* plugin_b, r_plugin_manager_t* plugin_manager);
typedef void (*PLBUPDATEFN)(plugin_b_t* plugin_b, f64 dt);
typedef void (*PRINTSUMFN)(plugin_b_t* plugin_b, i32 a, i32 b);

typedef struct plugin_b_api_t {
  void* handle;
  void (*init)(plugin_b_t* plugin_b, r_plugin_manager_t* plugin_manager);
  void (*update)(plugin_b_t* plugin_b, f64 dt);
  void (*print_sum)(plugin_b_t* plugin_b, i32 a, i32 b);
} plugin_b_api_t;

dll_export r_plugin_t* load_plugin_b(r_memory_t* memory, void* handle);
dll_export void plugin_b_init(plugin_b_t* plugin_b, r_plugin_manager_t* plugin_manager);
dll_export void plugin_b_update(plugin_b_t* plugin_b, f64 dt);
dll_export void plugin_b_print_sum(plugin_b_t* plugin_b, i32 a, i32 b);

#ifdef __cplusplus
}
#endif