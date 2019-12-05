#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

global char R_LOGGER_LOG_FILENAME[256] = "log.log";

typedef struct r_logger_t r_logger_t;

void //
r_logger_print(const char* format, ...);

void //
r_logger_print_test(r_logger_t* this, const char* format);

#ifdef __cplusplus
}
#endif