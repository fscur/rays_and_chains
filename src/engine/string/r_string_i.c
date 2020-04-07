#include "engine/memory/r_memory_arena.h"
#include "engine/app/r_api_db.h"
#include "r_string.h"
#include "r_string_i.h"

void //
r_string_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {
  r_string_i* string_api = r_memory_arena_push_struct(apis_arena, r_string_i);

  string_api->to_ansi = &r_string_to_ansi;
  string_api->copy_ansi = &r_string_copy_ansi;
  string_api->copy_wide = &r_string_copy_wide;

  r_api_db_add(api_db, R_STRING_API_NAME, string_api);
}