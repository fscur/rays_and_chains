#include "ui/imgui_impl_glfw_gl3.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct DebugInfo {
    int display_width;
    int display_height;
} DebugInfo;

static DebugInfo debug_info;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void render_debug_info() {
    ImGui_ImplGlfwGL3_NewFrame();
        
    igText("average: %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate, igGetIO()->Framerate);
    igText("width: %d height: %d", debug_info.display_width, debug_info.display_height);
    
    igRender();
}

void render_ui(GLFWwindow* window) {
    struct ImVec4 clear_color = (struct ImVec4) { 0.1f, 0.1f, 0.12f, 1.00f };
    
    glfwGetFramebufferSize(window, &debug_info.display_width, &debug_info.display_height);
    glViewport(0, 0, debug_info.display_width, debug_info.display_height);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    render_debug_info();

    glfwSwapBuffers(window);
}

GLFWwindow* initGLFW(const char* title, int width, int height) {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gl3wInit();
    return window;
}

void initImgui(GLFWwindow* window) {
    ImGui_ImplGlfwGL3_Init(window, true);
    
    struct ImGuiStyle* style = igGetStyle();
    igStyleColorsDark(style);

    struct ImGuiIO* io = igGetIO();
    ImFontAtlas_AddFontFromFileTTF(io->Fonts, "../res/fonts/UbuntuMono-Regular.ttf", 16.0f, 0, 0);
}

int main(int argc, char** args)
{
    GLFWwindow* window = initGLFW("rays and chains", 1280, 720);

    if (!window) {
        return 1;
    }

    initImgui(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        render_ui(window);
    }

    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}