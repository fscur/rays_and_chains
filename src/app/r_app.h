#pragma once

#include "r_bitmap.h"
#include "r_math.h"
#include "r_render.h"
#include "r_types.h"

typedef struct App_Window {
  void* handle;
  i32 width;
  i32 height;
} App_Window;

typedef struct App_Memory {
  u64 permanent_size;
  u8* permanent_addr;
  u64 transient_size;
  u8* transient_addr;
} App_Memory;

typedef struct App_State {
  App_Window* window;
  App_Memory* memory;
  Bitmap* image;
  u32 textureId;
  f32 dt;
  Color clear_color;
} App_State;

App_State* app_init(App_Window* window, App_Memory* memory);
void app_input(App_State* state);
void app_update(App_State* state);
void app_render(App_State* state);
void app_destroy(App_State* state);
