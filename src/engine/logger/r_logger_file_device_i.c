#include "engine/app/r_api_db.h"
#include "engine/memory/r_memory_arena.h"
#include "r_logger_file_device_i.h"
#include "r_logger_file_device.h"

void //
r_logger_file_device_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {
  r_logger_file_device_i* logger_file_device = r_memory_arena_push_struct(apis_arena, r_logger_file_device_i);

  logger_file_device->print = &r_logger_file_device_print;
  logger_file_device->set_filename = &r_logger_file_device_set_filename;

  r_api_db_add(api_db, R_LOGGER_FILE_DEVICE_API_NAME, logger_file_device);
}