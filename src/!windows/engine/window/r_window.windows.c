#include <stdio.h>
#include "engine/window/r_window.c"

void //
r_window_set_title(r_window_t* this, const wchar_t* title) {
  wsprintf(this->title, title);
  this->title_changed_callback(this);
}