#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global char R_DEBUG_LOG_FILENAME[256] = "log.log";

void //
r_debug_print(const char* format, ...);

#ifdef __cplusplus
}
#endif