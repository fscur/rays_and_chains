cls
@echo off
set "ROOT=..\.."
set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "WARNINGS=/WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054 /wd4200"

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
set "INCLUDE_DIRS=/I%ROOT%\src /I%ROOT%\inc"
set "COMMON_LINKER_FLAGS=-opt:ref /LIBPATH:%ROOT%\lib\windows\debug"

call log [info] "DEBUG"
echo.

pushd %ROOT%
if not exist build mkdir build
cd build
if not exist engine mkdir engine
popd

call log [info] "Building r_engine.com"

call utctag
set TAG=%_utctag%

pushd %ROOT%\build\engine
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_launcher.exe /Fmr_launcher.map /For_launcher.obj /TC "%ROOT%\src\engine\main\r_launcher.c" /link %COMMON_LINKER_FLAGS% /SUBSYSTEM:CONSOLE
popd
echo.

call log [info] "Copying output to bin"
pushd %ROOT%
echo f | xcopy .\build\engine\r_launcher.exe .\bin\r_engine.com /Y
popd