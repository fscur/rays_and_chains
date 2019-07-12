#include "r_main.h"
#include "engine/memory/r_memory.h"
#include "engine/time/r_datetime.h"
#include "engine/app/r_app_host.h"
#include "engine/thread/r_thread.h"
#include "engine/lib_loader/r_lib_loader.h"

void                                   //
r_main(r_main_info_t* main_info,       //
       R_RESULT_ON_SUCCESS on_success, //
       R_RESULT_ON_ERROR on_error) {

  f64 start;
  f64 last;

  r_thread_set_sleep_granularity(1);
  r_clock_init();
  last = start = r_datetime_now();

  r_frame_info_t frame_info = {0};
  size_t total_app_memory = r_app_get_size();
  r_memory_t memory = r_memory_create(total_app_memory + kilobytes(128));

  // todo: read from config file
  r_app_info_t app_info = {0};
  r_string_w_copy(L"rays and chains", app_info.title);
  app_info.width = 1280;
  app_info.height = 720;
  app_info.back_color = (r_color_t){1.00f, 0.09f, 0.12f, 1.00f};
  app_info.desired_fps = 60.0;
  app_info.frame_info = &frame_info;
  r_string_a_copy(main_info->app_filename, app_info.filename);

  r_app_host_t* app_host = r_app_host_create(&memory, &app_info);
  r_app_host_init(app_host);

  while (app_host->running) {
    r_debug_print(                                  //
        "[%010I64d][%08.3f][debug] Frame Start.\n", //
        frame_info.frame_count,
        frame_info.now / 1000.0);

    r_app_host_run(app_host);

    // todo: make timings be measured in seconds
    frame_info.dt = r_datetime_now() - last;

    // note: hold your horses, not so fast!
    if (frame_info.dt < frame_info.desired_ms_per_frame) {
      if (r_thread_sleep_is_granular) {
        i32 sleep_ms = (i32)(frame_info.desired_ms_per_frame - frame_info.dt) - 1;
        if (sleep_ms > 0)
          r_thread_sleep(sleep_ms);
      }

      assert(frame_info.dt < frame_info.desired_ms_per_frame);
      while (frame_info.dt < frame_info.desired_ms_per_frame) {
        frame_info.dt = r_datetime_now() - last;
      }
    } else if (frame_info.frame_count > 0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame lost! It took %5.2f ms.\n", //
          frame_info.frame_count,
          frame_info.now / 1000.0f,
          frame_info.dt);
    }

    f64 end = r_datetime_now();
    frame_info.dt = end - last;
    last = end;
    frame_info.now = last - start;

    // important:  wtf is going on here??? how does a frame jumps by more than 5.0 ms??? not cool.
    // try to understand it...
    if (frame_info.frame_count > 0 && frame_info.dt > frame_info.desired_ms_per_frame + 5.0) {
      r_debug_print(                                                   //
          "[%010I64d][%08.3f][debug] Frame drop? It took %5.2f ms.\n", //
          frame_info.frame_count,
          frame_info.now / 1000.0f,
          frame_info.dt);
    } else {
      r_debug_print(                                                  //
          "[%010I64d][%08.3f][debug] Frame End. It took %5.2f ms.\n", //
          frame_info.frame_count,
          frame_info.now / 1000.0f,
          frame_info.dt);
    }

    frame_info.frame_count++;
  }

  r_app_host_destroy(app_host);
}