#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_i r_api_db_i;

#define R_DEBUG_TEST_API_ID 259
#define R_DEBUG_TEST_API_NAME "r_debug_test"

typedef struct r_debug_t {
  int test;
} r_debug_t;

dll_export void //
r_debug_test_load(r_lib_load_info_t* load_info);

dll_export size_t //
r_debug_test_get_size();

dll_export u32 //
r_debug_test_get_id();

dll_export void //
r_debug_test_init(r_debug_t* this, r_api_db_i* api_db);

dll_export void //
r_debug_test_destroy(r_debug_t* this);

#ifdef __cplusplus
}
#endif