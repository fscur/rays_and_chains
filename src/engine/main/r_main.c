#include "r_main.h"
#include "engine/logger/r_logger.h"
#include "engine/time/r_datetime.h"
#include "engine/app/r_app_host.h"
#include "engine/thread/r_thread.h"
#include "engine/memory/r_memory.h"

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
  size_t app_host_size = r_app_host_get_size();
  r_memory_t memory = r_memory_create(app_host_size + kilobytes(128));

  r_app_host_t* app_host = r_app_host_create(&memory, &frame_info);
  r_logger_create(&frame_info);
  r_logger_file_device_set_filename(main_info->log_filename);

  r_app_host_load_app(app_host, main_info->app_filename);
  r_app_host_init(app_host);
  
  while (app_host->running) {
    r_logger_file_open();
    r_logger_debug("Frame Start.");
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
      r_logger_debug("Frame lost! It took %5.2f ms.", frame_info.dt);
    }

    f64 end = r_datetime_now();
    frame_info.dt = end - last;
    last = end;
    frame_info.now = last - start;

    // important:  wtf is going on here??? how does a frame jumps by more than 5.0 ms??? not cool.
    // try to understand it...
    if (frame_info.frame_count > 0 && frame_info.dt > frame_info.desired_ms_per_frame + 5.0) {
      r_logger_debug("Frame drop? It took %5.2f ms.", frame_info.dt);
    } else {
      r_logger_debug("Frame End. It took %5.2f ms.", frame_info.dt);
    }

    frame_info.frame_count++;
    r_logger_file_close();
  }

  r_logger_destroy();
  r_app_host_destroy(app_host);
}