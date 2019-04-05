#include "engine/window/r_window.h"
#include "engine/string/r_string.h"

void //
r_window_set_back_color(r_window_t* this, const r_color_t color) {
  this->back_color = color;

  if (this->back_color_changed_callback)
    this->back_color_changed_callback(this);
}