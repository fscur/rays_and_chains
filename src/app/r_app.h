#pragma once

#include "r_types.h"
#include "r_bitmap.h"
#include "r_math.h"
#include "r_window.h"
#include "r_ui.h"
#include "r_memory.h"

typedef struct App_State {
  App_Memory* memory;
  App_Window* window;
  App_Ui* ui;
  f32 dt;
  bool running;
} App_State;

typedef struct App_Code {
  void* lib_handle;
  App_State* (*create)(App_Memory*);
  void (*init)(App_State*);
  void (*load)(App_State*);
  void (*input)(App_State*);
  void (*update)(App_State*);
  void (*render)(App_State*);
  void (*unload)(App_State*);
  void (*destroy)(App_State*);
} App_Code;

// note: (filipe)
// create is where our memory is allocated
App_State* app_create(App_Memory* memory);

// note: (filipe)
// init occurs only once, before main loop
// destroy occurs only once, after main loop
// load/unload should be called every time the app is dynamically
// loaded/unloaded

void app_init(App_State* state);
void app_load(App_State* state);

void app_input(App_State* state);
void app_update(App_State* state);
void app_render(App_State* state);

void app_unload(App_State* state);
void app_destroy(App_State* state);
