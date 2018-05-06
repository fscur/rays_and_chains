#pragma once

#include "r_bitmap.h"
#include "r_math.h"
#include "r_render.h"
#include "r_types.h"

typedef struct App_Memory {
  u64 permanent_storage_size;
  u8* permanent_storage_addr;
  u64 transient_storage_size;
  u8* transient_storage_addr;
} App_Memory;

typedef struct App_State {
  App_Memory* memory;
  Bitmap* image;
  f32 dt;
  Color clear_color;
} App_State;

u32 get_int();

App_State* app_init(App_Memory* memory);

void app_destroy(App_State* state);
