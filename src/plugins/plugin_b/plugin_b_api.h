#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define PLUGIN_B_API_ID 257
#define PLUGIN_B_API_NAME = "plugin_b";

typedef struct plugin_b_t plugin_b_t;
typedef void (*PLUGIN_B_PRINT_SUM_PN)(plugin_b_t* this, i32 a, i32 b);

typedef struct plugin_b_api_t {
  PLUGIN_B_PRINT_SUM_PN print_sum;
} plugin_b_api_t;

#ifdef __cplusplus
}
#endif