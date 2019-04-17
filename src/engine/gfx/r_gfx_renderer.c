#include "r_gfx_renderer.h"

void //
r_gfx_renderer_add_cmd(r_gfx_renderer_t* this, r_gfx_cmd_t cmd) {
  this->cmd_buffer.keys[this->cmd_buffer.cmd_count] = cmd.key;
  this->cmd_buffer.data[this->cmd_buffer.cmd_count] = cmd.data;
  this->cmd_buffer.cmd_count++;
}

r_gfx_cmd_t* //
r_gfx_renderer_create_clear_color_buffer_cmd(r_gfx_renderer_t* this) {
  
  const r_color_t color = {
    .r = 1.0f,
    .g = 0.7f,
    .b = 0.5f,
    .a = 1.0f
  };
  
  r_gfx_clear_color_cmd_t clear_color_cmd = {
    .color=color
  };

  local r_gfx_cmd_t cmd = {0};
  cmd.key = 0;
  cmd.data = &clear_color_cmd;
  cmd.fn = this->clear_color_dispatcher;
  return &cmd;
}