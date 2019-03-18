cls
@echo off

set "DEFINES=/D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "WARNINGS=/WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054"

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
set "INCLUDE_DIRS=/I..\src /I..\inc"
set COMMON_LINKER_FLAGS="-opt:ref"

set VC14_PATH="%programfiles(x86)%\Microsoft Visual Studio 14.0\VC"
set VC17_PATH="%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build

if exist VC14_PATH goto vc14
if exist VC17_PATH goto vc17

:vc14
call %VC14_PATH%\vcvarsall.bat x64
goto start

:vc17
call %VC17_PATH%\vcvarsall.bat x64
goto start

:start

call log [info] "********** DEBUG **********"
call log [info] "Clearing previous build"
pushd p:\
if not exist bin mkdir bin
popd

call log [info] "Copying dependencies"
call log2 [info] & robocopy p:\lib\windows\x64\debug p:\bin *.dll /xo /njh /njs /ndl /nc /ns

call log [info] "Building sandbox.exe"
pushd p:\bin
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fesandbox.exe /Fmsandbox.map "..\src\!windows\sandbox\r_sandbox.c" /link %COMMON_LINKER_FLAGS%
popd

::dlls
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_memory.dll /Fmr_memory.map "..\src\!windows\engine\memory\r_memory.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_media.dll /Fmr_media.map "..\src\engine\media\r_media_bitmap.c" /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_gfx.dll /Fmr_gfx.map "..\src\engine\gfx\r_gfx.c" /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_plugin_loader.dll /Fmr_plugin_loader.map "..\src\!windows\engine\plugins\r_plugin_loader.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_plugin_manager.dll /Fmr_plugin_manager.map "..\src\engine\plugins\r_plugin_manager.c" r_memory.lib /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_window.dll /Fmr_window.map "..\src\!windows\engine\window\r_window.c" r_media.lib r_gfx.lib "../lib/windows/x64/release/glfw3.lib" kernel32.lib user32.lib gdi32.lib shell32.lib opengl32.lib /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_window.dll /Fmr_window.map "..\src\!windows\engine\window\r_window.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
::cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_app.dll /Fmr_app.map "..\src\!windows\engine\app\r_app.c" r_memory.lib r_window.lib /link /DLL %COMMON_LINKER_FLAGS%