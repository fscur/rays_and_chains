#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_DEBUG_API_ID 0
#define R_DEBUG_API_NAME "r_debug"

typedef void* (*R_DEBUG_PRINT)(const char* format, ...);

typedef struct r_debug_api_t {
  R_DEBUG_PRINT print;
} r_debug_api_t;

#ifdef __cplusplus
}
#endif