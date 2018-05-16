#include "r_app.h"
#include "r_raytracer.h"
#include "ui/imgui_impl_glfw_gl3.c"

typedef struct ImVec4 ImColor;
typedef struct ImVec2 ImVec2;
typedef struct ImVec4 ImVec4;
typedef struct ImGuiIO ImGuiIO;

void
update_gl_texture(u32 texID, Bitmap* image) {
  glBindTexture(GL_TEXTURE_2D, texID);
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               image->width,
               image->height,
               0,
               GL_BGRA,
               GL_UNSIGNED_BYTE,
               image->data);
}

void
render_raytracer_ui(App_State* state) {
  Color clear_color = state->clear_color;

  bool show_raytracer_window = true;
  igBegin("raytracer", &show_raytracer_window, 0);

  if (igButton("clear image!", (ImVec2){0, 0})) {
    r_clear_image(state->image, clear_color);
    update_gl_texture(state->textureId, state->image);
  }

  igSameLine(0, 2);

  if (igButton("load image", (ImVec2){0, 0})) {
    r_destroy_image(state->image);
    state->image = r_load_image("image.bmp");
    update_gl_texture(state->textureId, state->image);
  }

  igSameLine(0, 2);

  if (igButton("flip", (ImVec2){0, 0})) {
    r_flip_image(state->image);
    r_save_image(state->image, "image.bmp");
    update_gl_texture(state->textureId, state->image);
  }

  igSameLine(0, 2);

  if (igButton("raytrace!", (ImVec2){0, 0})) {
    state->dt += 0.01;
    start_raytracing(state->image, state->dt);
    r_save_image(state->image, "image.bmp");
    update_gl_texture(state->textureId, state->image);
  }

  igSameLine(0, 2);

  if (igButton("filipe!", (ImVec2){0, 0})) {
  }

  f32 uv_start = state->image->header.height < 0 ? 0.0f : 1.0f;
  f32 uv_end = state->image->header.height < 0 ? 1.0f : 0.0f;

  igImage((void*)state->textureId,
          (ImVec2){(f32)state->image->width, (f32)state->image->height},
          (ImVec2){uv_start, uv_start},
          (ImVec2){uv_end, uv_end},
          (ImColor){255, 255, 255, 255},
          (ImColor){255, 255, 255, 128});
  igEnd();
}

void
render_debug(const App_Window* window) {
  ImGuiIO* io = igGetIO();
  igText("average: %.3f ms/frame (%.1f FPS)",
         1000.0f / io->Framerate,
         io->Framerate);

  igText("width: %d height: %d", window->width, window->height);
}

void
render_imgui(App_State* state) {
  ImGui_ImplGlfwGL3_NewFrame();

  // bool open = true;
  // igShowDemoWindow(&open);

  render_debug(state->window);
  render_raytracer_ui(state);

  igRender();
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
  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               image->width,
               image->height,
               0,
               GL_BGRA,
               GL_UNSIGNED_BYTE,
               image->data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  return textureID;
}

App_State*
app_create(App_Memory* memory) {
  assert(sizeof(App_State) <= memory->permanent_size);

  App_State* state = (App_State*)memory->permanent_addr;
  state->running = true;
  state->memory = memory;
  state->image = r_create_image(400, 300);
  state->clear_color = (Color){0.4f, 0.1f, 0.12f, 1.00f};
  state->dt = 0.0;
  state->window = state + sizeof(App_State);

  App_Window* window = state->window;
  window->title = "rays and chains";
  window->width = 1280;
  window->height = 720;
  window->back_color = state->clear_color;

  r_clear_image(state->image, state->clear_color);
  return state;
}

void
app_init(App_State* state) {
  state->textureId = create_texture(state->image);
}

void
app_load(App_State* state) {
  init_imgui((GLFWwindow*)state->window->handle);
}

void
app_input(App_State* state) {
  window_input(state->window);
}

void
app_update(App_State* state) {
  state->dt = 0.1;
  state->clear_color = (Color){0.3f, 0.4f, 0.6f, 1.00f};
  state->window->back_color = state->clear_color;
  state->running = !state->window->should_close;
  window_update(state->window);
}

void
app_render(App_State* state) {
  window_render(state->window);
  render_imgui(state);
  window_swapbuffers(state->window);
}

void
app_unload(App_State* state) {
  ImGui_ImplGlfwGL3_Shutdown();
}

void
app_destroy(App_State* state) {
  window_destroy(state->window);
}