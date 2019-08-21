#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_api_db.h"
#include "engine/diagnostics/r_debug_api.h"
#include "engine/window/r_window.h"
#include "engine/window/r_window_api.h"
#include "engine/ui/r_ui_api.h"
#include "engine/string/r_string_api.h"
#include "engine/gfx/r_gfx_renderer.h"
#include "engine/gfx/r_gfx_renderer_api.h"

#include "ui.c"

#include "cimgui/cimgui.h"
#pragma comment(lib, "cimgui.lib")

#include <string.h>
#include <jansson/jansson.h>

#pragma comment(lib, "jansson_d.lib")

/*
int
main(int argc, char* argv[]) {
  size_t i;
  char* text;
  json_t* root;
  json_error_t error;

  text = "[{\"name\":\"filipe\"}]";

  if (!text)
    return 1;

  root = json_loads(text, 0, &error);
  //free(text);

  if (!root) {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return 1;
  }

  if (!json_is_array(root)) {
    fprintf(stderr, "error: root is not an array\n");
    json_decref(root);
    return 1;
  }

  for (i = 0; i < json_array_size(root); i++) {
    json_t *data, *name;

    data = json_array_get(root, i);
    if (!json_is_object(data)) {
      fprintf(stderr, "error: commit data %d is not an object\n", (int)(i + 1));
      json_decref(root);
      return 1;
    }

    name = json_object_get(data, "name");
    if (!json_is_string(name)) {
      fprintf(stderr, "error: commit %d: sha is not a string\n", (int)(i + 1));
      return 1;
    }

    printf("%s\n", json_string_value(name));
  }

  json_decref(root);
  return 0;
}
*/

u32 //
get_id_sandbox() {
  return 0;
}

size_t //
get_size_sandbox() {
  return sizeof(sandbox_t);
}

void //
load_sandbox(r_lib_load_info_t* load_info) {
  r_lib_t* lib = (r_lib_t*)load_info->lib_memory_addr;
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_get_app_info");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_init");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_run");
  lib->functions[lib->fn_count++] = load_info->fn(load_info->handle, "sandbox_destroy");
}

r_app_info_t //
sandbox_get_app_info() {
  
  r_app_info_t app_info = {
      .title = L"rays and chains", .width = 1920, .height = 1080, .desired_fps = 30.0};

  return app_info;
}

void //
sandbox_init(sandbox_t* this, r_api_db_t* api_db) {
  this->debug_api = api_db->apis[R_DEBUG_API_ID];
  this->window_api = api_db->apis[R_WINDOW_API_ID];
  this->ui_api = api_db->apis[R_UI_API_ID];
  this->string_api = api_db->apis[R_STRING_API_ID];
  this->renderer_api = api_db->apis[R_GFX_RENDERER_API_ID];

  init_ui();

  // note: ui api prototype
  // r_ui_t* ui = this->ui_api->ui;
  // r_ui_canvas_t* canvas = this->ui_api->create_canvas(ui, 800, 600);
  // r_ui_menu_t* menu = this->ui_api->create_menu(canvas);

  // r_ui_menu_item_t* file_menu_item = this->ui_api->create_menu_item(menu, "File");
  // r_ui_menu_item_t* edit_menu_item = this->ui_api->create_menu_item(menu, "Edit");
  // r_ui_menu_item_t* tools_menu_item = this->ui_api->create_menu_item(menu, "Tools");
  // r_ui_menu_item_t* windows_menu_item = this->ui_api->create_menu_item(menu, "Windows");
  // r_ui_menu_item_t* help_menu_item = this->ui_api->create_menu_item(menu, "Help");

  // this->ui_api->add_menu_item(menu, file_menu_item);
  // this->ui_api->add_menu_item(menu, edit_menu_item);
  // this->ui_api->add_menu_item(menu, tools_menu_item);
  // this->ui_api->add_menu_item(menu, windows_menu_item);
  // this->ui_api->add_menu_item(menu, help_menu_item);

  // this->ui_api->add_menu(canvas, menu);
  // this->ui_api->add_canvas(ui, canvas);
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  r_window_t* window = this->window_api->window;

  this->window_api->input(window);
  this->window_api->update(window);

  r_gfx_renderer_t* renderer = this->renderer_api->renderer;
  r_gfx_cmd_t* cmd = this->renderer_api->create_clear_color_cmd(renderer);

  r_gfx_clear_color_cmd_t* clear_color_cmd = (r_gfx_clear_color_cmd_t*)cmd->data;
  clear_color_cmd->color = window->back_color;

  this->renderer_api->clear(renderer);
  this->renderer_api->add_cmd(renderer, cmd);
  this->renderer_api->sort(renderer);
  this->renderer_api->submit(renderer);

  r_ui_t* ui = this->ui_api->ui;

  // note: gambis, will think about it later
  this->ui_api->begin(ui);
  render_ui();
  this->ui_api->end(ui);

  this->window_api->swap_buffers(window);
}

void //
sandbox_destroy(sandbox_t* this) {}