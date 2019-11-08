#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;

typedef void (*R_API_DB_ADD)(r_api_db_t* db, u32 api_id, const char* api_name, void* handle);
typedef void* (*R_API_DB_FIND_BY_NAME)(const r_api_db_t* db, const char* api_name);

typedef struct r_api_db_i {
  r_api_db_t* instance;
  R_API_DB_ADD add;
  R_API_DB_FIND_BY_NAME find_by_name;
} r_api_db_i;

#ifdef __cplusplus
}
#endif