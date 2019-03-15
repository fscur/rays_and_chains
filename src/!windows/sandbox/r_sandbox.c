#include <windows.h>
#include <stdio.h>
#include "!windows/engine/diagnostics/r_debug.c"
#include "!windows/engine/memory/r_memory.c"
#include "!windows/engine/window/r_window.c"
#include "engine/app/r_app.c"

typedef struct r_time_t {
  f64 clock_frequency;
  f64 desired_fps;
  f64 desired_ms_per_frame;
  f64 dt;
  f64 now;
  i64 frames;
} r_time_t;

f64 //
r_time_get_clock_frequency_in_ms() {
  LARGE_INTEGER clock_frequency;
  QueryPerformanceFrequency(&clock_frequency);
  return 1000.0 / (f64)clock_frequency.QuadPart;
}

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

  LARGE_INTEGER start;
  LARGE_INTEGER last;
  LARGE_INTEGER current;

  QueryPerformanceCounter(&start);
  last = start;

  r_memory_t memory = r_memory_create(kilobytes(1));

  // todo: read from file
  r_app_info_t app_info = {0};
  sprintf(app_info.title, "rays and chains");
  app_info.width = 1280;
  app_info.height = 720;
  app_info.back_color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};

  r_app_t* app = r_app_create(&memory, &app_info);

  r_time_t app_time = {0};
  app_time.clock_frequency = r_time_get_clock_frequency_in_ms();
  app_time.desired_fps = 60.0;
  app_time.desired_ms_per_frame = 1000.0 / app_time.desired_fps;

  r_window_create(app->window);

  r_app_init(app);
  r_app_load(app);

  while (app->running) {

    r_app_run(app);

    QueryPerformanceCounter(&current);
    app_time.dt = (current.QuadPart - last.QuadPart) * app_time.clock_frequency;

    // note: hold your horses! not too fast!
    while (app_time.dt <= app_time.desired_ms_per_frame) {
      QueryPerformanceCounter(&current);
      app_time.dt = (current.QuadPart - last.QuadPart) * app_time.clock_frequency;
    }

    app_time.now = (current.QuadPart - start.QuadPart) * app_time.clock_frequency;

    last = current;
    app->dt = app_time.dt;

    r_debug_print(                                     //
        "[frame - %010d][%4.2f][debug] elapsed: %f\n", //
        app_time.frames,
        app_time.now / 1000.0,
        app_time.dt);

    app_time.frames++;
  }

  r_app_unload(app);
  r_app_destroy(app);

  return 0;
}