#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "apps/sandbox/sandbox.c"

void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db) {

  // this->app_api->init = (R_APP_INIT)load_info->fn(load_info->handle, "sandbox_init");
  // this->app_api->run = (R_APP_RUN)load_info->fn(load_info->handle, "sandbox_run");
  // this->app_api->destroy = (R_APP_DESTROY)load_info->fn(load_info->handle, "sandbox_destroy");

  this->debug_api = api_db->apis[R_DEBUG_API_ID];
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  this->debug_api->print("Running.");
}

void //
sandbox_destroy(sandbox_t* this) {}