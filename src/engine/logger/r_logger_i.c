#include "engine/app/r_api_db.h"
#include "engine/memory/r_memory_arena.h"
#include "r_logger_i.h"
#include "r_logger.h"

void //
r_logger_register_api(r_api_db_t* api_db, r_memory_arena_t* apis_arena) {  
  r_logger_i* logger = r_memory_arena_push_struct(apis_arena, r_logger_i);

  logger->add_device = &r_logger_add_device;
  logger->debug = &r_logger_debug;
  logger->warn = &r_logger_warn;
  logger->error = &r_logger_error;
  logger->fatal = &r_logger_fatal;

  r_api_db_add(api_db, R_LOGGER_API_NAME, logger);
}

