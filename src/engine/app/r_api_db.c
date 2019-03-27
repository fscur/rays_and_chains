#include "r_api_db.h"

void* //
r_api_db_find_api(r_api_db_t* this, const u32 id) {
  return this->apis[id];
}