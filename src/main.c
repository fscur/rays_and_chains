#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "ui/imgui_impl_glfw_gl3.c"
#include "r_math.h"
#include "r_bitmap.h"
#include "r_world.h"

typedef struct ImVec4 ImColor;
typedef struct ImVec2 ImVec2;
typedef struct ImVec4 ImVec4;
typedef struct ImGuiIO ImGuiIO;

typedef struct DebugInfo {
    int display_width;
    int display_height;
} DebugInfo;

u32 texID;
Bitmap* image;
bool show_raytracer_window = true;

static void error_callback(const int error, const char *description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void render_debug_info(const DebugInfo debug_info) {

    ImGuiIO* io = igGetIO();
    igText("average: %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    igText("width: %d height: %d", debug_info.display_width, debug_info.display_height);
}

Color li(World* world, Ray ray) {
    f32 t_min = world->camera.far;

    if (ray_plane_intersection(ray, world->floor, &t_min))
        return (Color){ 1.0f, 0.0f, 0.0f, 1.0f };
    else
        return world->sky_color;
}

void start_raytracing(float t) {
    
    Camera camera = { 0 };
    camera.near = 1.0;
    camera.far = 1001.0;
    camera.fov = 90;
    camera.position = (v3) { 0.0, 0.1, 1.0 };
    camera.look_at = (v3) { 0.0, 0.0, 0.0 };
    
    camera.up = (v3) { 0.0, 1.0, 0.0 };
    camera.direction = norm3(-camera.position);
    camera.right = norm3(cross3(camera.up, camera.direction));
    camera.up = norm3(cross3(camera.direction, camera.right));

    Plane plane = {0};
    plane.position = (v3) { 0.0f , 0.0f , 0.0f };
    plane.normal = (v3) { 0.0f, 1.0f, 0.0f };
    World world = {0};
    world.sky_color = (Color) { 0.5f, 0.6f, 0.8f, 1.0f};
    world.camera = camera;
    world.floor = plane;

    f32 x, y, w, h;

    w = (f32)image->width;
    h = (f32)image->height;

    f32 x_factor = 1.0f/w;
    f32 y_factor = 1.0f/h;
    f32 x_aspect = w > h ? w/h : 1.0f;
    f32 y_aspect = h > w ? h/w : 1.0f;

    u32* pixels = image->data;

    v3 film_z = mul3(camera.direction, camera.near);

    for (y = 0; y < h; ++y) {
        v3 film_y = mul3(camera.up, (y * y_factor * 2.0f - 1.0f) * y_aspect);

        for (x = 0.0f; x < w; ++x) {
            v3 film_x = mul3(camera.right, (x * x_factor * 2.0f - 1.0f) * x_aspect);
            v3 film_pos = add3(add3(film_x, film_y), film_z);
            Ray ray = { camera.position, norm3(film_pos) };

            Color color = li(&world, ray);

            u8 r = round_f32_to_i32(color.r * 255.0f);
            u8 g = round_f32_to_i32(color.g * 255.0f);
            u8 b = round_f32_to_i32(color.b * 255.0f);
            u8 a = round_f32_to_i32(color.a * 255.0f);

            *pixels++ = from_u8_to_32(a, r, g, b);
        }
    }
    
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->data);
}
f32 t0 = 0.0;
void render_raytracer_ui() {
    if (show_raytracer_window) {
        igBegin("raytracer", &show_raytracer_window, 0);

        //static int clicked = 0;
        if (igButton("raytrace!", (ImVec2) { 0, 0 })) {
            t0 -=0.001;
            start_raytracing(t0);
        }

        igImage(
            (void*)texID, 
            (ImVec2) { (f32)image->width,(f32)image->height }, 
            (ImVec2) { 0, 0 }, 
            (ImVec2) { 1, 1 }, 
            (ImColor) { 255, 255, 255, 255}, 
            (ImColor) { 255, 255, 255, 128});
        igEnd();
    }
}

void render_ui(GLFWwindow *window) {
    ImVec4 clear_color = (ImVec4){0.1f, 0.1f, 0.12f, 1.00f};
    DebugInfo debug_info = {};

    glfwGetFramebufferSize(window, &debug_info.display_width, &debug_info.display_height);
    glViewport(0, 0, debug_info.display_width, debug_info.display_height);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplGlfwGL3_NewFrame();
    bool open = true; igShowDemoWindow(&open);
    render_debug_info(debug_info);
    render_raytracer_ui();
    igRender();
}

GLFWwindow *init_glfw(const char *title, const int width, const int height) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gl3wInit();
    return window;
}

void init_imgui(GLFWwindow *window) {
    ImGui_ImplGlfwGL3_Init(window, true);

    struct ImGuiStyle *style = igGetStyle();
    igStyleColorsDark(style);

    struct ImGuiIO *io = igGetIO();
    ImFontAtlas_AddFontFromFileTTF(io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

u32 create_texture(Bitmap* image) {
    GLuint textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, image->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    return textureID;
}

int main(int argc, char** args) {

    GLFWwindow* window = init_glfw("rays and chains", 1280, 720);

    if (!window) {
        return 1;
    }

    init_imgui(window);

    image = rc_create_image(640, 480);
    Color clear_color = { 1.0f, 0.0f, 0.0f, 1.0f };
    rc_clear_image(image, clear_color);
    texID = create_texture(image);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();        
        render_ui(window);

        glfwSwapBuffers(window);
    }

    rc_destroy_image(image);
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}