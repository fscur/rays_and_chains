#include "r_api_db.h"
#include "engine\string\r_string.h"

void //
r_api_db_add(r_api_db_t* db, u32 api_id, const char* api_name, void* api_handle) {
  assert(r_string_len(api_name) < MAX_API_NAME_LENGTH);
  r_string_a_copy(api_name, db->names[api_id]);
  db->apis[api_id] = api_handle;
}

void* //
r_api_db_find_by_name(const r_api_db_t* db, const char* api_name) {
  for (int i = 0; i < MAX_APIS; ++i) {
    if (r_string_cmp(db->names[i], api_name) == 0)
      return db->apis[i];
  }
  return NULL;
}