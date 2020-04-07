#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_api_db_t r_api_db_t;
typedef struct r_memory_arena_t r_memory_arena_t;

dll_export r_api_db_t* //
r_api_db_create(r_memory_arena_t* memory_arena);

dll_export void //
r_api_db_add(r_api_db_t* db, const char* api_name, void* handle);

dll_export void* //
r_api_db_find_by_name(const r_api_db_t* db, const char* api_name);

dll_export void //
r_api_db_destroy(r_api_db_t* db);

#ifdef __cplusplus
}
#endif