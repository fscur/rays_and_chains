#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

// note: (filipe.scur) half space of db is reserved to the engine apis
// maybe it would be better to treat them separetely... we'll see...
// it was chosen to be this way, so not everything needs to be a plugin

#define MAX_APIS 512
#define MAX_PLUGIN_APIS 256

#define r_memory_block_push_struct(arena_ptr, type)                                                \
  (type*)r_memory_block_push(arena_ptr, sizeof(type))

typedef struct r_api_db_t r_api_db_t;
typedef void* (*R_API_DB_FIND_API_FN)(r_api_db_t*, const u32, const u32);

typedef struct r_api_db_t {
  R_API_DB_FIND_API_FN find_api;
  void* apis[MAX_APIS];
  u32 dependency_graph[MAX_PLUGIN_APIS][MAX_PLUGIN_APIS];
} r_api_db_t;

dll_export void* //
r_api_db_find_api(r_api_db_t* this, const u32 api_id, const u32 dependent_id);

dll_export void //
r_api_db_get_dependency_reload_order(r_api_db_t* this,
                                     const u32 api_id,
                                     u32* ordered_api_ids,
                                     u32* count);

#ifdef __cplusplus
}
#endif