#include "r_gfx_renderer.h"

void //
r_gfx_renderer_add_cmd(r_gfx_renderer_t* this, r_gfx_cmd_t cmd) {
  this->cmd_buffer[this->cmd_buffer.cmd_count++] = cmd;
}