#define _GNU_SOURCE
#include <sys/mman.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../app/r_app.h"
#include "ui/imgui_impl_glfw_gl3.c"

typedef struct ImVec4 ImColor;
typedef struct ImVec2 ImVec2;
typedef struct ImVec4 ImVec4;
typedef struct ImGuiIO ImGuiIO;

typedef struct DebugInfo {
  i32 display_width;
  i32 display_height;
} DebugInfo;

u32 texID;

static void
error_callback(const int error, const char* description) {
  fprintf(stderr, "Error %d: %s\n", error, description);
}

void
render_debug_info(const DebugInfo debug_info) {
  ImGuiIO* io = igGetIO();
  igText("average: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate,
         io->Framerate);
  igText("width: %d height: %d", debug_info.display_width,
         debug_info.display_height);
}

void
update_gl_texture(u32 texID, Bitmap* image) {
  glBindTexture(GL_TEXTURE_2D, texID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0,
               GL_BGRA, GL_UNSIGNED_BYTE, image->data);
}

void
render_raytracer_ui(App_State* state) {
  Color clear_color = state->clear_color;

  bool show_raytracer_window = true;
  igBegin("raytracer", &show_raytracer_window, 0);

  if (igButton("clear!", (ImVec2){0, 0})) {
    r_clear_image(state->image, clear_color);
    update_gl_texture(texID, state->image);
  }

  igSameLine(0, 2);

  if (igButton("load", (ImVec2){0, 0})) {
    r_destroy_image(state->image);
    state->image = r_load_image("image.bmp");
    update_gl_texture(texID, state->image);
  }

  igSameLine(0, 2);

  if (igButton("flip", (ImVec2){0, 0})) {
    r_flip_image(state->image);
    r_save_image(state->image, "image.bmp");
    update_gl_texture(texID, state->image);
  }

  igSameLine(0, 2);

  if (igButton("raytrace!", (ImVec2){0, 0})) {
    state->dt += 0.01;
    start_raytracing(state->image, state->dt);
    r_save_image(state->image, "image.bmp");
    update_gl_texture(texID, state->image);
  }

  f32 uv_start = state->image->header.height < 0 ? 0.0f : 1.0f;
  f32 uv_end = state->image->header.height < 0 ? 1.0f : 0.0f;

  igImage((void*)texID,
          (ImVec2){(f32)state->image->width, (f32)state->image->height},
          (ImVec2){uv_start, uv_start}, (ImVec2){uv_end, uv_end},
          (ImColor){255, 255, 255, 255}, (ImColor){255, 255, 255, 128});
  igEnd();
}

void
render_ui(GLFWwindow* window, App_State* state) {
  ImVec4 clear_color = (ImVec4){0.1f, 0.1f, 0.12f, 1.00f};
  DebugInfo debug_info = {};

  glfwGetFramebufferSize(window, &debug_info.display_width,
                         &debug_info.display_height);
  glViewport(0, 0, debug_info.display_width, debug_info.display_height);
  glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplGlfwGL3_NewFrame();

  // bool open = true;
  // igShowDemoWindow(&open);

  render_debug_info(debug_info);
  render_raytracer_ui(state);

  igRender();
}

GLFWwindow*
init_glfw(const char* title, const int width, const int height) {
  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    return NULL;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);
  gl3wInit();

  return window;
}

void
init_imgui(GLFWwindow* window) {
  ImGui_ImplGlfwGL3_Init(window, true);

  struct ImGuiStyle* style = igGetStyle();
  igStyleColorsDark(style);

  struct ImGuiIO* io = igGetIO();
  ImFontAtlas_AddFontFromFileTTF(
      io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

u32
create_texture(Bitmap* image) {
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0,
               GL_BGRA, GL_UNSIGNED_BYTE, image->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  return textureID;
}

// char* dll_name = "libr_app.so";
// char * functionname = "get_int";
// void* handle = dlopen(dll_name, RTLD_NOW);
// if (!handle) {
//     fprintf(stderr, "Couldn't open handle: %s\n",
//         dlerror());
//     exit(1);
// }

// int (*fun)() = (int (*)())dlsym(handle, functionname);
// if (fun == NULL) {
//     fprintf(stderr, "Couldn't find function: %s\n",functionname);
//     exit(1);
// }
// int a = fun();
// printf("result: %d \n", a);

int
main(int argc, char** args) {
  GLFWwindow* window = init_glfw("rays and chains", 1280, 720);

  if (!window)
    return 1;

  init_imgui(window);

#if _DEBUG
  void* base_addr = (void*)gigabytes(1);
#else
  void* base_addr = 0;
#endif
  // todo: (filipe)
  // allocate transient storage memory

  App_Memory memory = {};
  memory.permanent_storage_size = megabytes(512);
  memory.permanent_storage_addr =
      mmap(base_addr, memory.permanent_storage_size, PROT_NONE,
           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

  u32 res = mprotect(memory.permanent_storage_addr,
                     memory.permanent_storage_size, PROT_READ | PROT_WRITE);

  // note: (filipe)
  // if mprotect() fails we could not allocate all memory necessary and we
  // should quit

  assert(res == 0);

  App_State* state = app_init(&memory);

  texID = create_texture(state->image);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    // todo: (filipe)
    // input();

    render_ui(window, state);

    // render_scene();
    // update();

    glfwSwapBuffers(window);
  }

  // todo: (filipe)
  // should we not manually release our memory?
  // munmap(memory.permanent_storage_addr, memory.permanent_storage_size);

  app_destroy(state);

  ImGui_ImplGlfwGL3_Shutdown();
  glfwTerminate();

  return 0;
}