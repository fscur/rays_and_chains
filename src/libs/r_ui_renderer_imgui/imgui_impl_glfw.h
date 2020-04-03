// dear imgui: Platform Binding for GLFW
// This needs to be used along with a Renderer (e.g. OpenGL3, Vulkan..)
// (Info: GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// Implemented features:
//  [X] Platform: Clipboard support.
//  [X] Platform: Gamepad support. Enable with 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad'.
//  [x] Platform: Mouse cursor shape and visibility. Disable with 'io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange'. FIXME: 3 cursors types are missing from GLFW.
//  [X] Platform: Keyboard arrays indexed using GLFW_KEY_* codes, e.g. ImGui::IsKeyPressed(GLFW_KEY_SPACE).

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// About GLSL version:
// The 'glsl_version' initialization parameter defaults to "#version 150" if NULL.
// Only override if your GL version doesn't handle this GLSL version. Keep NULL if unsure!

#pragma once

// clang-format off
#ifndef IM_ASSERT
#define IM_ASSERT(_EXPR)            assert(_EXPR)                               // You can override the default assert handler by editing imconfig.h
#endif
#if defined(__clang__) || defined(__GNUC__)
#define IM_FMTARGS(FMT)             __attribute__((format(printf, FMT, FMT+1))) // Apply printf-style warnings to user functions.
#define IM_FMTLIST(FMT)             __attribute__((format(printf, FMT, 0)))
#else
#define IM_FMTARGS(FMT)
#define IM_FMTLIST(FMT)
#endif
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))         // Size of a static C-style array. Don't use on pointers!
#define IM_OFFSETOF(_TYPE,_MEMBER)  ((size_t)&(((_TYPE*)0)->_MEMBER))           // Offset of _MEMBER within _TYPE. Standardized as offsetof() in modern C++.
#define IM_UNUSED(_VAR)             ((void)_VAR)                                // Used to silence "unused variable warnings". Often useful as asserts may be stripped out from final builds.
// clang-format on

typedef struct GLFWwindow GLFWwindow;

CIMGUI_API bool     ImGui_ImplGlfw_InitForOpenGL(GLFWwindow* window, bool install_callbacks);
CIMGUI_API bool     ImGui_ImplGlfw_InitForVulkan(GLFWwindow* window, bool install_callbacks);
CIMGUI_API void     ImGui_ImplGlfw_Shutdown();
CIMGUI_API void     ImGui_ImplGlfw_NewFrame();

// InitXXX function with 'install_callbacks=true': install GLFW callbacks. They will call user's previously installed callbacks, if any.
// InitXXX function with 'install_callbacks=false': do not install GLFW callbacks. You will need to call them yourself from your own GLFW callbacks.
CIMGUI_API void     ImGui_ImplGlfw_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
CIMGUI_API void     ImGui_ImplGlfw_ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
CIMGUI_API void     ImGui_ImplGlfw_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
CIMGUI_API void     ImGui_ImplGlfw_CharCallback(GLFWwindow* window, unsigned int c);
