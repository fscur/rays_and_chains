#include "engine/memory/r_memory_arena.h"
#include "engine/app/r_api_db.h"
#include "r_window.h"
#include "r_window_i.h"

void //
r_window_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {
  r_window_i* window_api = r_memory_arena_push_struct(apis_arena, r_window_i);

  window_api->set_backcolor = &r_window_set_backcolor;
  window_api->set_title = &r_window_set_title;
  window_api->create = &r_window_create;
  window_api->show = &r_window_show;
  window_api->process_input = &r_window_process_input;

  r_api_db_add(api_db, R_WINDOW_API_NAME, window_api);
}