#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef void* (*R_DEBUG_PRINT)(const char* format, ...);

typedef struct r_debug_api_t {
  void* (*print)(const char* format, ...);
} r_debug_api_t;

void //
r_debug_print(const char* format, ...);

#ifdef __cplusplus
}
#endif