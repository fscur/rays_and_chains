#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;

typedef r_api_db_t* (*R_API_DB_CREATE)();
typedef void (*R_API_DB_ADD)(r_api_db_t* db, const char* api_name, void* handle);
typedef void* (*R_API_DB_FIND_BY_NAME)(const r_api_db_t* db, const char* api_name);
typedef void (*R_API_DB_DESTROY)(r_api_db_t*);

typedef struct r_api_db_i {
  r_api_db_t* instance;
  R_API_DB_CREATE create;
  R_API_DB_ADD add;
  R_API_DB_FIND_BY_NAME find_by_name;
  R_API_DB_DESTROY destroy;
} r_api_db_i;

#ifdef __cplusplus
}
#endif