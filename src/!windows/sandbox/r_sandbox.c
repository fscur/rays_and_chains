#include <windows.h>
#include <stdio.h>
#include "engine/plugins/r_plugin_manager.h"
#include "engine/memory/r_memory.h"
#include "engine/window/r_window.h"
#include "engine/app/r_app.h"
#include "engine/plugins/r_plugin_loader.h"

#define R_MEMORY_API "r_memory.dll"
#define R_MEMORY_API_CREATE "r_memory_create"

r_memory_api //
load_memory_api() {
  r_memory_api api = {0};
  api.handle = r_plugin_loader_load_plugin(R_MEMORY_API);
  api.create = (R_MEMORY_CREATE)r_plugin_loader_fn(api.handle, R_MEMORY_API_CREATE);
  return api;
}

#define R_PLUGIN_MANAGER_API "r_plugin_manager.dll"
#define R_PLUGIN_MANAGER_API_CREATE "r_plugin_manager_create"
#define R_PLUGIN_MANAGER_API_ADD "r_plugin_manager_add"
#define R_PLUGIN_MANAGER_API_REMOVE "r_plugin_manager_remove"
#define R_PLUGIN_MANAGER_API_FIND "r_plugin_manager_find"

r_plugin_manager_api //
load_plugin_manager_api() {
  r_plugin_manager_api api = {0};
  api.handle = r_plugin_loader_load_plugin(R_PLUGIN_MANAGER_API);
  api.create = (R_PLUGIN_MANAGER_CREATE)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_CREATE);
  api.add = (R_PLUGIN_MANAGER_ADD)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_ADD);
  api.remove = (R_PLUGIN_MANAGER_REMOVE)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_REMOVE);
  api.find = (R_PLUGIN_MANAGER_FIND)r_plugin_loader_fn(api.handle, R_PLUGIN_MANAGER_API_FIND);
  return api;
}

#define R_APP_API "r_app.dll"
#define R_APP_API_CREATE "r_app_create"
#define R_APP_API_RUN "r_app_run"
#define R_APP_API_INIT "r_app_init"
#define R_APP_API_LOAD "r_app_load"
#define R_APP_API_INPUT "r_app_input"
#define R_APP_API_UPDATE "r_app_update"
#define R_APP_API_RENDER "r_app_render"
#define R_APP_API_UNLOAD "r_app_unload"
#define R_APP_API_DESTROY "r_app_destroy"

r_app_api //
load_app_api() {
  r_app_api api = {0};
  api.handle = r_plugin_loader_load_plugin(R_APP_API);
  api.create = (R_APP_CREATE)r_plugin_loader_fn(api.handle, R_APP_API_CREATE);
  api.run = (R_APP_RUN)r_plugin_loader_fn(api.handle, R_APP_API_RUN);
  api.init = (R_APP_INIT)r_plugin_loader_fn(api.handle, R_APP_API_INIT);
  api.load = (R_APP_LOAD)r_plugin_loader_fn(api.handle, R_APP_API_LOAD);
  api.input = (R_APP_INPUT)r_plugin_loader_fn(api.handle, R_APP_API_INPUT);
  api.update = (R_APP_UPDATE)r_plugin_loader_fn(api.handle, R_APP_API_UPDATE);
  api.render = (R_APP_INIT)r_plugin_loader_fn(api.handle, R_APP_API_RENDER);
  api.unload = (R_APP_LOAD)r_plugin_loader_fn(api.handle, R_APP_API_UNLOAD);
  api.destroy = (R_APP_INPUT)r_plugin_loader_fn(api.handle, R_APP_API_DESTROY);
  return api;
}

void //
unload_app_api(void* handle) {
  r_plugin_loader_unload_plugin(handle);
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

  r_memory_api memory_api = load_memory_api();
  r_memory_t memory = memory_api.create(megabytes(500), megabytes(10));

  r_plugin_manager_api plugin_manager_api = load_plugin_manager_api();
  r_plugin_manager_state_t* plugin_manager_state = plugin_manager_api.create(&memory);

  r_app_api app = load_app_api();

  plugin_manager_api.add(plugin_manager_state, R_APP_API, &app, sizeof(r_app_state_t));

  r_app_info_t app_info = {0};
  sprintf(app_info.title, "rays and chains");
  app_info.width = 1280;
  app_info.height = 720;
  app_info.back_color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};

  r_app_state_t* app_state = app.create(plugin_manager_state->memory_arena, app_info);

  r_window_create(app_state->window);

  app.init(app_state);
  app.load(app_state);

  while (app_state->running) {
    app.input(app_state);
    app.update(app_state);
    app.render(app_state);
    // unload_app_api(app.handle);
    // app = load_app_api();
  }

  app.unload(app_state);
  app.destroy(app_state);

  return 0;
}