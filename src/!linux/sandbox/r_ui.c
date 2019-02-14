#include "engine/app/r_app_ui.h"
#include "engine/gfx/r_gfx_raytracer.h"
#include "sandbox/ui/imgui_impl_glfw_gl3.c"

typedef struct ImVec4 ImColor;
typedef struct ImVec2 ImVec2;
typedef struct ImVec4 ImVec4;
typedef struct ImGuiIO ImGuiIO;

internal void
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

internal void
render_raytracer_ui(App_Ui* ui) {
  Color clear_color = ui->clear_color;

  bool show_raytracer_window = true;
  igBegin("raytracer", &show_raytracer_window, 0);

  if (igButton("clear!", (ImVec2){0, 0})) {
    r_clear_image(ui->image, clear_color);
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("load", (ImVec2){0, 0})) {
    r_destroy_image(ui->image);
    ui->image = r_load_image("image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("flip", (ImVec2){0, 0})) {
    r_flip_image(ui->image);
    r_save_image(ui->image, "image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("raytrace!", (ImVec2){0, 0})) {
    ui->dt += 0.01;
    start_raytracing(ui->image, ui->dt);
    r_save_image(ui->image, "image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  f32 uv_start = ui->image->header.height < 0 ? 0.0f : 1.0f;
  f32 uv_end = ui->image->header.height < 0 ? 1.0f : 0.0f;

  igImage((void*)ui->texture_id,
          (ImVec2){(f32)ui->image->width, (f32)ui->image->height},
          (ImVec2){uv_start, uv_start},
          (ImVec2){uv_end, uv_end},
          (ImColor){255, 255, 255, 255},
          (ImColor){255, 255, 255, 128});
  igEnd();
}

internal void
render_debug(App_Ui* ui) {
  ImGuiIO* io = igGetIO();
  igText("average: %.3f ms/frame (%.1f FPS)",
         1000.0f / io->Framerate,
         io->Framerate);

  igText("width: %d height: %d", ui->window->width, ui->window->height);
}

internal void
render_imgui(App_Ui* ui) {
  ImGui_ImplGlfwGL3_NewFrame();

  // bool open = true;
  // igShowDemoWindow(&open);

  render_debug(ui);
  render_raytracer_ui(ui);

  igRender();
}

internal void
init_imgui(App_Ui* ui) {
  ImGui_ImplGlfwGL3_Init(ui->window->handle, true);

  struct ImGuiStyle* style = igGetStyle();
  igStyleColorsDark(style);

  struct ImGuiIO* io = igGetIO();
  ImFontAtlas_AddFontFromFileTTF(
      io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

internal u32
create_texture(Bitmap* image) {
  GLuint texture_id;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
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
  return texture_id;
}

void
ui_init(App_Ui* ui) {
  ui->texture_id = create_texture(ui->image);
}

void
ui_load(App_Ui* ui) {
  init_imgui(ui);
}

void
ui_render(App_Ui* ui) {
  render_imgui(ui);
}

void
ui_unload(App_Ui* ui) {
  ImGui_ImplGlfwGL3_Shutdown();
}