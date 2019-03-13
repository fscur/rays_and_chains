cls
@echo off

set "COMMON_COMPILER_FLAGS=/MD /nologo /Gm- /GR- /EHa- /Od /Oi /WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /FC /Z7 /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "INCLUDE_DIRS=/I..\src /I..\inc"
set COMMON_LINKER_FLAGS=""

call "%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64

call log [info] "********** DEBUG **********"

call log [info] "Clearing previous build"

pushd p:\
rmdir bin /s /q
mkdir bin
popd

call log [info] "Copying dependencies"
call log2 [info] & xcopy p:\lib\windows\x64\debug\cimgui.dll p:\bin 

call log [info] "Building sandbox.exe"

pushd p:\bin
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_memory.dll /Fmr_memory.map "..\src\!windows\engine\memory\r_memory.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_media.dll /Fmr_media.map "..\src\engine\media\r_media_bitmap.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_gfx.dll /Fmr_gfx.map "..\src\engine\gfx\r_gfx.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_plugin_manager.dll /Fmr_plugin_manager.map "..\src\engine\plugins\r_plugin_manager.c" r_memory.lib /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_app.dll /Fmr_app.map "..\src\!windows\engine\app\r_app.c" r_memory.lib r_media.lib r_gfx.lib "../lib/windows/x64/release/glfw3.lib" "../lib/windows/x64/release/cimgui.lib" kernel32.lib user32.lib gdi32.lib shell32.lib opengl32.lib /link /DLL
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fesandbox.exe /Fmsandbox.map "..\src\!windows\sandbox\r_sandbox.c" /link
popd
::kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

::call log2 [file] & call cl_dll_debug "r_memory" "..\src\!windows\engine\memory\r_memory.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_dll_debug "r_plugin_manager" "..\src\engine\plugins\r_plugin_manager.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_dll_debug "r_app" "..\src\engine\app\r_app.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_exe_debug "sandbox" "..\src\!windows\sandbox\r_sandbox.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
