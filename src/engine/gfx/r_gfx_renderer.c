#include "r_gfx_renderer.h"

r_gfx_cmd_t* //
r_gfx_renderer_create_clear_color_buffer_cmd(const r_gfx_renderer_t* this) {
  
  r_color_t color = {
    .r = 1.0f,
    .g = 0.7f,
    .b = 0.5f,
    .a = 1.0f
  };
  
  local r_gfx_clear_color_cmd_t clear_color_cmd = {0};
  clear_color_cmd.color = color;

  local r_gfx_cmd_t cmd = {0};
  cmd.key = 0;
  cmd.data = &clear_color_cmd;
  cmd.fn = this->clear_color_dispatcher;
  return &cmd;
}

void //
r_gfx_renderer_add_cmd(r_gfx_renderer_t* this, r_gfx_cmd_t cmd) {
  this->cmd_buffer.keys[this->cmd_buffer.cmd_count] = cmd.key;
  this->cmd_buffer.data[this->cmd_buffer.cmd_count] = cmd.data;
  this->cmd_buffer.fn[this->cmd_buffer.cmd_count] = cmd.fn;
  this->cmd_buffer.cmd_count++;
}

void //
r_gfx_renderer_clear(r_gfx_renderer_t* this) {
  this->cmd_buffer.cmd_count = 0;
}

void //
r_gfx_renderer_sort(r_gfx_renderer_t* this) {

}

void //
r_gfx_renderer_submit(const r_gfx_renderer_t* this) {
  for (int i = 0; i < this->cmd_buffer.cmd_count; ++i) {
    this->cmd_buffer.fn[i](this->cmd_buffer.data[i]);
  }
}