#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "apps/hammer/hammer.c"

void //
hammer_init(hammer_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
}

void //
hammer_run(hammer_t* this, r_frame_info_t* frame_info) {
  this->debug_api->print("Running.");
}

void //
hammer_destroy(hammer_t* this) {}