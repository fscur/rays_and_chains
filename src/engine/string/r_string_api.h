#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

#define R_STRING_API_ID 2
#define R_STRING_API_NAME "r_string"

typedef void (*R_STRING_TO_ANSI)(wchar_t* wide_string, char* ansi_string, size_t length);

typedef struct r_string_api_t {
  R_STRING_TO_ANSI to_ansi;
} r_string_api_t;

#ifdef __cplusplus
}
#endif