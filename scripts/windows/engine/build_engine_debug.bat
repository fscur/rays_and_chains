cls
@echo off
set "ROOT=..\.."
set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "WARNINGS=/WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054"

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
set "INCLUDE_DIRS=/I%ROOT%\src /I%ROOT%\inc"
set "COMMON_LINKER_FLAGS=-opt:ref /LIBPATH:%ROOT%\lib\windows\x64\debug"

set VC14_PATH="%programfiles(x86)%\Microsoft Visual Studio 14.0\VC"
set VC17_PATH="%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build"

if /I exist %VC14_PATH% (
  goto vc14
)

if /I exist %VC17_PATH% ( 
  goto vc17
)

:vc14
call %VC14_PATH%\vcvarsall.bat x64
goto start

:vc17
call %VC17_PATH%\vcvarsall.bat x64
goto start

:start
echo.
echo.
call log [info] "DEBUG"
echo.

pushd %ROOT%
if not exist build mkdir build
cd build
if not exist engine mkdir engine
popd

call log [info] "Copying dependencies"
call log2 [info] & robocopy %ROOT%\lib\windows\x64\debug %ROOT%\bin *.dll /xo /njh /njs /ndl /nc /ns
echo.

call log [info] "Building r_engine.exe"

call utctag
set TAG=%_utctag%

pushd %ROOT%\build\engine
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_time.dll /Fmr_time.map "%ROOT%\src\!windows\engine\time\r_time.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_io.dll /Fmr_io.map "%ROOT%\src\!windows\engine\io\r_io.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_string.dll /Fmr_string.map "%ROOT%\src\!windows\engine\string\r_string.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_memory.dll /Fmr_memory.map "%ROOT%\src\!windows\engine\memory\r_memory.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_plugins.dll /Fmr_plugins.map "%ROOT%\src\!windows\engine\plugins\r_plugins.windows.c" /link /DLL %COMMON_LINKER_FLAGS%
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Fer_engine.exe /Fmr_engine.map "%ROOT%\src\!windows\engine\main\r_main.windows.c" /link %COMMON_LINKER_FLAGS%
popd
echo.

call log [info] "Copying output to bin"
pushd %ROOT%
robocopy .\build\engine .\bin *.pdb /xo /njh /njs /ndl /nc /ns /nfl
robocopy .\build\engine .\bin *.dll /xo /njh /njs /ndl /nc /ns /nfl
robocopy .\build\engine .\bin *.exe /xo /njh /njs /ndl /nc /ns /nfl
robocopy .\build\engine .\lib\windows\x64\debug *.lib /xo /njh /njs /ndl /nc /ns /nfl
popd