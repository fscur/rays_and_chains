// dear imgui: Renderer for modern OpenGL with shaders / programmatic pipeline
// - Desktop GL: 2.x 3.x 4.x
// - Embedded GL: ES 2.0 (WebGL 1.0), ES 3.0 (WebGL 2.0)
// This needs to be used along with a Platform Binding (e.g. GLFW, SDL, Win32, custom..)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'GLuint' OpenGL texture identifier as void*/ImTextureID. Read the FAQ about ImTextureID!
//  [x] Renderer: Desktop GL only: Support for large meshes (64k+ vertices) with 16-bit indices.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.

// About GLSL version:
//  The 'glsl_version' initialization parameter should be NULL (default) or a "#version XXX" string.
//  On computer platform the GLSL version default to "#version 130". On OpenGL ES 3 platform it defaults to "#version 300 es"
//  Only override if your GL version doesn't handle this GLSL version. See GLSL version table at the top of imgui_impl_opengl3.cpp.

#pragma once
#include "engine/core/r_core_types.h"

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

// Backend API
CIMGUI_API bool     ImGui_ImplOpenGL3_Init(const char* glsl_version);
CIMGUI_API void     ImGui_ImplOpenGL3_Shutdown();
CIMGUI_API void     ImGui_ImplOpenGL3_NewFrame();
CIMGUI_API void     ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data);

// (Optional) Called by Init/NewFrame/Shutdown
CIMGUI_API bool     ImGui_ImplOpenGL3_CreateFontsTexture();
CIMGUI_API void     ImGui_ImplOpenGL3_DestroyFontsTexture();
CIMGUI_API bool     ImGui_ImplOpenGL3_CreateDeviceObjects();
CIMGUI_API void     ImGui_ImplOpenGL3_DestroyDeviceObjects();

// Specific OpenGL versions
//#define IMGUI_IMPL_OPENGL_ES2     // Auto-detected on Emscripten
//#define IMGUI_IMPL_OPENGL_ES3     // Auto-detected on iOS/Android

// Desktop OpenGL: attempt to detect default GL loader based on available header files.
// If auto-detection fails or doesn't select the same GL loader file as used by your application,
// you are likely to get a crash in ImGui_ImplOpenGL3_Init().
// You can explicitly select a loader by using '#define IMGUI_IMPL_OPENGL_LOADER_XXX' in imconfig.h or compiler command-line.
#if !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
    #if defined(__has_include)
        #if __has_include(<GL/glew.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLEW
        #elif __has_include(<glad/glad.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLAD
        #elif __has_include(<GL/gl3w.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GL3W
        #elif __has_include(<glbinding/gl/gl.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLBINDING
        #else
            #error "Cannot detect OpenGL loader!"
        #endif
    #else
        #define IMGUI_IMPL_OPENGL_LOADER_GL3W       // Default to GL3W
    #endif
#endif

