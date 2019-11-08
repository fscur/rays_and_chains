#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

// note: (filipe.scur) half space of db is reserved to the engine apis
// maybe it would be better to treat them separetely... we'll see...
// it was chosen to be this way, so not everything needs to be a plugin
#define MAX_API_NAME_LENGTH 32
#define MAX_APIS 512
#define MAX_PLUGIN_APIS 256

// todo: create hashtable to save apis names
typedef struct r_api_db_t {
  char names[MAX_APIS][MAX_API_NAME_LENGTH];
  void* apis[MAX_APIS];
} r_api_db_t;

dll_export void //
r_api_db_add(r_api_db_t* db, u32 api_id, const char* api_name, void* handle);

dll_export void* //
r_api_db_find_by_name(const r_api_db_t* db, const char* api_name);

#ifdef __cplusplus
}
#endif