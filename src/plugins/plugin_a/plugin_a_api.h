#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

// important: (filipe.scur@gmail.com)
// this should be unique! we have to find a way to have it be unique!

#define PLUGIN_A_API_ID 257
#define PLUGIN_A_API_NAME "plugin_a"

typedef i32 (*PLUGIN_A_ADD_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_A_SUB_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_A_MUL_FN)(i32 a, i32 b);
typedef i32 (*PLUGIN_A_DIV_FN)(i32 a, i32 b);

typedef struct plugin_a_api_t {
  PLUGIN_A_ADD_FN add;
  PLUGIN_A_SUB_FN sub;
  PLUGIN_A_MUL_FN mul;
  PLUGIN_A_DIV_FN div;
} plugin_a_api_t;

#ifdef __cplusplus
}
#endif