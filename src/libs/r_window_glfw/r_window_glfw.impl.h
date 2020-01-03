#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "engine/core/r_core_types.h"

typedef struct r_window_t r_window_t;
typedef struct r_window_desc_t r_window_desc_t;

r_window_t* //
r_window_glfw_create(r_window_desc_t* window_descriptor);

void //
r_window_glfw_show(r_window_t* window);

void //
r_window_glfw_hide(r_window_t* window);

void //
r_window_glfw_process_input(r_window_t* window);

void //
r_window_glfw_set_title(r_window_t* window, const wchar_t* title);

void //
r_window_glfw_set_back_color(r_window_t* window, const r_color_t color);

void //
r_window_glfw_swap_buffers(const r_window_t* window);

void //
r_window_glfw_destroy_impl();

#ifdef __cplusplus
}
#endif