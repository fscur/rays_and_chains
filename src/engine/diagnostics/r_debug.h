#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global char R_DEBUG_LOG_FILENAME[256] = "log.log";

typedef struct r_debug_t r_debug_t;

void //
r_debug_print(const char* format, ...);

void //
r_debug_print_test(r_debug_t* this, const char* format);

#ifdef __cplusplus
}
#endif