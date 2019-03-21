#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define PLUGIN_A_NAME "plugin_a"

typedef struct r_plugin_manager_t r_plugin_manager_t;
typedef struct r_plugin_t r_plugin_t;
typedef struct r_memory_t r_memory_t;

typedef void (*PLUGINAINITFN)(void* plugin_a, r_plugin_manager_t* plugin_manager);
typedef void (*PLUGINAUPDATEFN)(void* plugin_a, f64 dt);
typedef i32 (*ADDFN)(i32, i32);
typedef i32 (*SUBFN)(i32, i32);
typedef i32 (*MULFN)(i32, i32);
typedef i32 (*DIVFN)(i32, i32);

typedef struct plugin_a_api_t {
  void* handle;
  void (*init)(void* plugin_a, r_plugin_manager_t* plugin_manager);
  void (*update)(void* plugin_a, f64 dt);
  i32 (*add)(i32, i32);
  i32 (*sub)(i32, i32);
  i32 (*mul)(i32, i32);
  i32 (*div)(i32, i32);
} plugin_a_api_t;

dll_export r_plugin_t* load_plugin_a(r_memory_t* memory, void* handle);
dll_export void plugin_a_init(void* plugin_a, r_plugin_manager_t* plugin_manager);
dll_export void plugin_a_update(void* plugin_a, f64 dt);

dll_export i32 plugin_a_add(i32 a, i32 b);
dll_export i32 plugin_a_sub(i32 a, i32 b);
dll_export i32 plugin_a_mul(i32 a, i32 b);
dll_export i32 plugin_a_div(i32 a, i32 b);

#ifdef __cplusplus
}
#endif