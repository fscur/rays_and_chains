#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef i32 (*PLUGIN_A_ADD_FN)(i32, i32);
typedef i32 (*PLUGIN_A_SUB_FN)(i32, i32);
typedef i32 (*PLUGIN_A_MUL_FN)(i32, i32);
typedef i32 (*PLUGIN_A_DIV_FN)(i32, i32);

typedef struct plugin_a_api_t {
  PLUGIN_A_ADD_FN add;
  PLUGIN_A_SUB_FN sub;
  PLUGIN_A_MUL_FN mul;
  PLUGIN_A_DIV_FN div;
  //i32 (*add)(i32, i32);
  // i32 (*sub)(i32, i32);
  // i32 (*mul)(i32, i32);
  // i32 (*div)(i32, i32);
} plugin_a_api_t;

dll_export i32 plugin_a_add(i32 a, i32 b);
dll_export i32 plugin_a_sub(i32 a, i32 b);
dll_export i32 plugin_a_mul(i32 a, i32 b);
dll_export i32 plugin_a_div(i32 a, i32 b);

#ifdef __cplusplus
}
#endif