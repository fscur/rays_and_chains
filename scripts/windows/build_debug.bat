cls
@echo off

set COMMON_COMPILER_FLAGS="/MT /nologo /Gm- /GR- /EHa- /Od /Oi /WX /W4 /wd4100 /FC /Z7 /D_DEBUG /DWIN32"
set INCLUDE_DIRS="/I..\src"
set COMMON_LINKER_FLAGS=""

call "%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64

call log [info] "********** DEBUG **********"

call log [info] "Clearing previous build"

pushd p:\
rmdir bin /s /q
mkdir bin
popd

call log [info] "Building sandbox.exe"
call log2 [file] & call cl_dll_debug "r_memory" "..\src\!windows\engine\memory\r_memory.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
call log2 [file] & call cl_dll_debug "r_plugin_manager" "..\src\engine\plugins\r_plugin_manager.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
call log2 [file] & call cl_dll_debug "r_app" "..\src\engine\app\r_app.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
call log2 [file] & call cl_exe_debug "sandbox" "..\src\!windows\sandbox\r_sandbox.c" %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% %COMMON_LINKER_FLAGS%
