#include <windows.h>
#include <stdio.h>
#include "!windows/engine/diagnostics/r_debug.windows.c"
#include "!windows/engine/memory/r_memory.windows.c"
#include "!windows/engine/window/r_window.windows.c"
#include "!windows/engine/app/r_app.windows.c"
#include "!windows/engine/time/r_time.windows.c"

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

  f64 start;
  f64 last;
  f64 current;

  r_time_init_clock_frequency();
  last = start = r_time_now();

  r_memory_t memory = r_memory_create(kilobytes(1));

  // todo: read from file
  r_app_info_t app_info = {0};
  sprintf(app_info.title, "rays and chains");
  app_info.width = 1280;
  app_info.height = 720;
  app_info.back_color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};

  r_app_t* app = r_app_create(&memory, &app_info);

  r_time_t app_time = {0};
  app_time.desired_fps = 60.0;
  app_time.desired_ms_per_frame = 1000.0 / app_time.desired_fps;

  r_window_create(app->window);

  r_app_init(app);
  r_app_load(app);

  while (app->running) {

    r_app_run(app);

    current = r_time_now();
    app_time.dt = current - last;

    // note: hold your horses! not too fast!
    while (app_time.dt <= app_time.desired_ms_per_frame) {
      current = r_time_now();
      app_time.dt = current - last;
    }

    app_time.now = current - start;

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