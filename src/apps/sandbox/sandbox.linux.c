#include "sandbox.h"
#include "engine/app/r_app.h"
#include "engine/app/r_app_i.h"
#include "engine/app/r_api_db_i.h"

u32 //
sandbox_get_id(void) {
  return 0;
}

size_t //
sandbox_get_api_size(void) {
  return sizeof(r_app_i);
}

size_t //
sandbox_get_size(void) {
  return sizeof(sandbox_t);
}

void //
sandbox_load(r_lib_load_info_t* load_info) {
  r_app_i* app_api = (r_app_i*)load_info->api_memory_addr;
  app_api->get_app_info = (R_APP_GET_APP_INFO)load_info->fn(load_info->handle, "sandbox_get_app_info");
  app_api->init = (R_APP_INIT)load_info->fn(load_info->handle, "sandbox_init");
  app_api->run = (R_APP_RUN)load_info->fn(load_info->handle, "sandbox_run");
  app_api->destroy = (R_APP_DESTROY)load_info->fn(load_info->handle, "sandbox_destroy");
}

r_app_info_t //
sandbox_get_app_info(void) {

  r_app_info_t app_info = {.title = L"sandbox app", .width = 1280, .height = 720, .desired_fps = 30.0};

  return app_info;
}

void //
sandbox_init(r_app_t* app, r_api_db_i* api_db) {
  printf("Init.\n");
}

void //
sandbox_run(sandbox_t* this, r_frame_info_t* frame_info) {
  printf("Running.\n");
}

void //
sandbox_destroy(sandbox_t* this) {
  printf("Destroy.\n");
}