#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef void* (*R_API_DB_FIND_API_FN)(r_api_db_t*, const u32);

typedef struct r_api_db_t {
  R_API_DB_FIND_API_FN find;
  void* apis[512];
} r_api_db_t;

dll_export void* //
r_api_db_find_api(r_api_db_t* this, const u32 id);

#ifdef __cplusplus
}
#endif