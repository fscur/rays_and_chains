#include "hammer.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"

u32 //
get_id_hammer(void) {
  return 0;
}

size_t //
get_size_hammer(void) {
  return sizeof(hammer_t);
}

void //
load_hammer(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "hammer_destroy");
}

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