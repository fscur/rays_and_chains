#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "engine/window/r_window.h"
#include "engine/plugins/r_plugin.h"
#include "apps/sandbox/sandbox.c"

void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
}

void //
sandbox_input(sandbox_t* this) {
}

void //
sandbox_update(sandbox_t* this, f64 dt) {
}

void //
sandbox_render(sandbox_t* this) {
}

void //
sandbox_destroy(sandbox_t* this) {
}