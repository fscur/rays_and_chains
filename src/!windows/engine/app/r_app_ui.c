#include "engine/app/r_app_ui.h"
#include "engine/media/r_media_bitmap.h"
#include "engine/gfx/r_gfx_raytracer.h"
#include "imgui_impl_opengl3.c"
#include "imgui_impl_glfw.c"

internal void
update_gl_texture(u32 texID, r_media_bitmap_t* image) {
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
render_raytracer_ui(r_app_ui_t* ui) {
  r_color_t clear_color = ui->clear_color;

  bool show_raytracer_window = true;
  igBegin("raytracer", &show_raytracer_window, 0);

  if (igButton("clear!", (ImVec2){0, 0})) {
    r_media_clear_image(ui->image, clear_color);
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("load", (ImVec2){0, 0})) {
    r_media_destroy_image(ui->image);
    ui->image = r_media_load_image("image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("flip", (ImVec2){0, 0})) {
    r_media_flip_image(ui->image);
    r_media_save_image(ui->image, "image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  igSameLine(0, 2);

  if (igButton("raytrace!", (ImVec2){0, 0})) {
    ui->dt += 0.01f;
    r_gfx_raytracer_start_raytracing(ui->image, ui->dt);
    r_media_save_image(ui->image, "image.bmp");
    update_gl_texture(ui->texture_id, ui->image);
  }

  f32 uv_start = ui->image->header.height < 0 ? 0.0f : 1.0f;
  f32 uv_end = ui->image->header.height < 0 ? 1.0f : 0.0f;

  igImage((void*)ui->texture_id,
          (ImVec2){(f32)ui->image->width, (f32)ui->image->height},
          (ImVec2){uv_start, uv_start},
          (ImVec2){uv_end, uv_end},
          (ImVec4){255, 255, 255, 255},
          (ImVec4){255, 255, 255, 128});
  igEnd();
}

internal void
render_debug(r_app_ui_t* ui) {
  // ImGuiIO* io = igGetIO();
  // igText("average: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);

  // igText("width: %d height: %d", ui->window->width, ui->window->height);
}

internal void
render_imgui(r_app_ui_t* ui) {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  igNewFrame();

  // bool open = true;
  // igShowDemoWindow(&open);

  render_debug(ui);
  render_raytracer_ui(ui);

  igRender();
  ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
}

ImGuiContext* ctx;

internal void
init_imgui(r_app_ui_t* ui) {

  const char* glsl_version = "#version 130";
  ctx = igCreateContext(NULL);
  ImGui_ImplGlfw_InitForOpenGL(ui->window->handle, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  struct ImGuiStyle* style = igGetStyle();
  igStyleColorsDark(style);

  struct ImGuiIO* io = igGetIO();
  ImFontAtlas_AddFontFromFileTTF(io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

internal u32
create_texture(r_media_bitmap_t* image) {
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
r_app_ui_init(r_app_ui_t* ui) {
  ui->texture_id = create_texture(ui->image);
}

void
r_app_ui_load(r_app_ui_t* ui) {
  init_imgui(ui);
}

void
r_app_ui_render(r_app_ui_t* ui) {
  render_imgui(ui);
}

void
r_app_ui_unload(r_app_ui_t* ui) {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  igDestroyContext(ctx);
}