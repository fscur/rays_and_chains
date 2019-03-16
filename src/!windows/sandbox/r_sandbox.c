#include <windows.h>
#include <stdio.h>
#include "!windows/engine/diagnostics/r_debug.windows.c"
#include "!windows/engine/memory/r_memory.windows.c"
#include "!windows/engine/thread/r_thread.windows.c"
#include "!windows/engine/time/r_time.windows.c"
#include "!windows/engine/window/r_window.windows.c"
#include "!windows/engine/app/r_app.windows.c"

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  f64 start;
  f64 last;
  // f64 current;

  r_thread_set_sleep_granularity(1);
  r_time_init_clock_frequency();
  last = start = r_time_now();

  r_time_t time = {0};
  r_memory_t memory = r_memory_create(kilobytes(64));

  // todo: read from file
  r_app_info_t app_info = {0};
  sprintf(app_info.title, "rays and chains");
  app_info.width = 400;
  app_info.height = 300;
  app_info.back_color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};
  app_info.desired_fps = 30.0;
  app_info.time = &time;

  r_app_t* app = r_app_create(&memory, &app_info);

  r_window_create(app->window);

  r_app_init(app);
  r_app_load(app);

  while (app->running) {
    r_debug_print(                                  //
        "[%010I64d][%08.3f][debug] Frame Start.\n", //
        time.frames,
        time.now / 1000.0);

    r_app_run(app);

    // todo: make timings be measured in seconds
    time.dt = r_time_now() - last;

    // note: hold your horses, not so fast!
    if (time.dt < time.desired_ms_per_frame) {
      if (r_thread_sleep_is_granular) {
        i32 sleep_ms = (i32)(time.desired_ms_per_frame - time.dt) - 1;
        if (sleep_ms > 0)
          r_thread_sleep(sleep_ms);
      }

      assert(time.dt < time.desired_ms_per_frame);
      while (time.dt < time.desired_ms_per_frame) {
        time.dt = r_time_now() - last;
      }
    } else if (time.frames > 0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame lost! It took %5.2f ms.\n", //
          time.frames,
          time.now / 1000.0f,
          time.dt);
    }

    f64 end = r_time_now();
    time.dt = end - last;
    last = end;
    time.now = last - start;

    // important:  wtf is going on here??? how does a frame jumps by more than 5.0 ms??? not cool.
    if (time.frames > 0 && time.dt > time.desired_ms_per_frame + 5.0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame drop? It took %5.2f ms.\n", //
          time.frames,
          time.now / 1000.0f,
          time.dt);
    } else {
      r_debug_print(                                                  //
          "[%010I64d][%08.3f][debug] Frame End. It took %5.2f ms.\n", //
          time.frames,
          time.now / 1000.0f,
          time.dt);
    }

    time.frames++;
  }

  r_app_unload(app);
  r_app_destroy(app);

  return 0;
}