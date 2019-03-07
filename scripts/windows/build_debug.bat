cls
@echo off

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi /WX /W4 /wd4100 /wd4204 /FC /Z7 /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS"
set INCLUDE_DIRS="..\src"
set COMMON_LINKER_FLAGS=""

call "%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64

call log [info] "********** DEBUG **********"

call log [info] "Clearing previous build"

pushd p:\
rmdir bin /s /q
mkdir bin
popd

call log [info] "Building sandbox.exe"


pushd p:\bin
cl /I%INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_memory.dll /Fmr_memory.map "..\src\!windows\engine\memory\r_memory.c" /link /DLL %COMMON_LINKER_FLAGS%
cl /I%INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_media.dll /Fmr_media.map "..\src\engine\media\r_media_bitmap.c" /link /DLL %COMMON_LINKER_FLAGS%
cl /I%INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_plugin_manager.dll /Fmr_plugin_manager.map "..\src\engine\plugins\r_plugin_manager.c" r_memory.lib /link /DLL %COMMON_LINKER_FLAGS%
cl /I%INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_app.dll /Fmr_app.map "..\src\engine\app\r_app.c" r_memory.lib r_media.lib /link /DLL %COMMON_LINKER_FLAGS%
cl /I%INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fesandbox.exe /Fmsandbox.map "..\src\!windows\sandbox\r_sandbox.c" /link %COMMON_LINKER_FLAGS%
popd

::call log2 [file] & call cl_dll_debug "r_memory" "..\src\!windows\engine\memory\r_memory.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_dll_debug "r_plugin_manager" "..\src\engine\plugins\r_plugin_manager.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_dll_debug "r_app" "..\src\engine\app\r_app.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
::call log2 [file] & call cl_exe_debug "sandbox" "..\src\!windows\sandbox\r_sandbox.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
