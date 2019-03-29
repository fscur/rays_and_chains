#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define PLUGIN_C_API_ID 258
#define PLUGIN_C_API_NAME "plugin_c"

typedef i32 (*PLUGIN_C_ADD_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_C_SUB_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_C_MUL_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_C_DIV_FN)(i32 a, i32 b);

typedef struct plugin_c_api_t {
  PLUGIN_C_ADD_FN add;
  PLUGIN_C_SUB_FN sub;
  PLUGIN_C_MUL_FN mul;
  PLUGIN_C_DIV_FN div;
} plugin_c_api_t;

#ifdef __cplusplus
}
#endif