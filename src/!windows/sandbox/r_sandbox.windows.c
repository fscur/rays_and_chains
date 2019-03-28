
#include <windows.h>
#include <stdio.h>
#include "!windows/engine/diagnostics/r_debug.windows.c"
#include "!windows/engine/memory/r_memory.windows.c"
#include "!windows/engine/thread/r_thread.windows.c"
#include "!windows/engine/time/r_time.windows.c"
#include "!windows/engine/window/r_window.windows.c"
#include "!windows/engine/app/r_app.windows.c"
#include "!windows/engine/plugins/r_plugins.windows.c"

int CALLBACK
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
  f64 start;
  f64 last;

  r_thread_set_sleep_granularity(1);
  r_time_init_clock_frequency();
  last = start = r_time_now();

  r_time_info_t time_info = {0};
  size_t total_app_memory = r_app_get_size();
  r_memory_t memory = r_memory_create(total_app_memory + kilobytes(64));

  // todo: read from file
  r_app_info_t app_info = {0};
  wsprintf(app_info.title, L"rays and chains");
  app_info.width = 400;
  app_info.height = 300;
  app_info.back_color = (r_color_t){0.08f, 0.09f, 0.12f, 1.00f};
  app_info.desired_fps = 30.0;
  app_info.time_info = &time_info;

  r_app_t* app = r_app_create(&memory, &app_info);

  r_window_create(app->window);

  r_app_init(app);
  r_app_load(app);

  while (app->running) {
    r_debug_print(                                  //
        "[%010I64d][%08.3f][debug] Frame Start.\n", //
        time_info.frames,
        time_info.now / 1000.0);

    r_app_run(app);

    // todo: make timings be measured in seconds
    time_info.dt = r_time_now() - last;

    // note: hold your horses, not so fast!
    if (time_info.dt < time_info.desired_ms_per_frame) {
      if (r_thread_sleep_is_granular) {
        i32 sleep_ms = (i32)(time_info.desired_ms_per_frame - time_info.dt) - 1;
        if (sleep_ms > 0)
          r_thread_sleep(sleep_ms);
      }

      assert(time_info.dt < time_info.desired_ms_per_frame);
      while (time_info.dt < time_info.desired_ms_per_frame) {
        time_info.dt = r_time_now() - last;
      }
    } else if (time_info.frames > 0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame lost! It took %5.2f ms.\n", //
          time_info.frames,
          time_info.now / 1000.0f,
          time_info.dt);
    }

    f64 end = r_time_now();
    time_info.dt = end - last;
    last = end;
    time_info.now = last - start;

    // important:  wtf is going on here??? how does a frame jumps by more than 5.0 ms??? not cool.
    // try to understand it...
    if (time_info.frames > 0 && time_info.dt > time_info.desired_ms_per_frame + 5.0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame drop? It took %5.2f ms.\n", //
          time_info.frames,
          time_info.now / 1000.0f,
          time_info.dt);
    } else {
      r_debug_print(                                                  //
          "[%010I64d][%08.3f][debug] Frame End. It took %5.2f ms.\n", //
          time_info.frames,
          time_info.now / 1000.0f,
          time_info.dt);
    }

    time_info.frames++;
  }

  r_app_unload(app);
  r_app_destroy(app);

  return 0;
}