#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_DEBUG_API_ID 1
#define R_DEBUG_API_NAME "r_debug"

typedef struct r_debug_t r_debug_t;

typedef void (*R_DEBUG_PRINT)(const char* format, ...);
typedef void (*R_DEBUG_PRINT_TEST)(r_debug_t* instance, const char* format);

typedef struct r_debug_i {
  r_debug_t* instance;
  R_DEBUG_PRINT print;
  R_DEBUG_PRINT_TEST print_test;
} r_debug_i;

#ifdef __cplusplus
}
#endif