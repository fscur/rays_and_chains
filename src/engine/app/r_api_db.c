#include "r_api_db.h"
#include "engine/string/r_string.h"
#include "engine/collections/r_hashtable.h"
#include "engine/memory/r_memory_arena.h"
#include <stdlib.h>

typedef struct r_hashtable_t r_hashtable_t;

typedef struct r_api_db_t {
  r_hashtable_t* apis;
} r_api_db_t;

r_api_db_t* //
r_api_db_create(r_memory_arena_t* memory_arena) {
  r_hashtable_t* apis = r_hashtable_create();
  r_api_db_t* db = r_memory_arena_push_struct(memory_arena, r_api_db_t);
  db->apis = apis;
  return db;
}

void //
r_api_db_add(r_api_db_t* db, const char* api_name, void* api_handle) {
  r_hashtable_add(db->apis, api_name, api_handle);
}

void* //
r_api_db_find_by_name(const r_api_db_t* db, const char* api_name) {
  return r_hashtable_find(db->apis, api_name);
}

void //
r_api_db_destroy(r_api_db_t* db) {
  r_hashtable_destroy(db->apis);
  free(db);
}