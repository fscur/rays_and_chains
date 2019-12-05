#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_LOGGER_API_ID 1
#define R_LOGGER_API_NAME "r_debug"

typedef struct r_logger_t r_logger_t;

typedef void (*R_LOGGER_PRINT)(const char* format, ...);
typedef void (*R_LOGGER_PRINT_TEST)(r_logger_t* instance, const char* format);

typedef struct r_logger_i {
  r_logger_t* instance;
  R_LOGGER_PRINT print;
  R_LOGGER_PRINT_TEST print_test;
} r_logger_i;

#ifdef __cplusplus
}
#endif