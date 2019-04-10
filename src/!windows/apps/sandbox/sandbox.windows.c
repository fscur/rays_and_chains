#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "apps/sandbox/sandbox.c"

void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window_api->window;
  this->window_api->clear_color(window);
  this->window_api->input(window);
  this->window_api->update(window);

  r_ui_t* ui = this->ui_api->ui;
  this->ui_api->render(ui);

  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}