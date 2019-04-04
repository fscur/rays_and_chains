cls
@echo off
set "APP_NAME=%1"
set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "WARNINGS=/WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054"

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
set "INCLUDE_DIRS=/I..\src /I..\inc"
set COMMON_LINKER_FLAGS="-opt:ref"

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

call log [info] "********** DEBUG **********"
pushd P:\
del build\apps\%APP_NAME%*.* /Q
del build\apps\%APP_NAME%\%APP_NAME%* /Q
if not exist build mkdir build
cd build
if not exist apps mkdir apps
cd apps
if not exist %APP_NAME% mkdir %APP_NAME%
popd

call log [info] "Building %APP_NAME%.dll"

call utctag
set TAG=%_utctag%

call log2 [info]
pushd p:\
.\tools\bumpver\bumpver.exe -b ".\src\apps\%APP_NAME%\version.rc"
popd

call log [info] "Compiling %APP_NAME%.dll resources"
pushd p:\
rc /d DEBUG ".\src\apps\%APP_NAME%\version.rc"
cd build
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% "..\src\!windows\apps\%APP_NAME%\%APP_NAME%.windows.c" /Fe"apps\%APP_NAME%\%APP_NAME%.dll" /Fm"apps\%APP_NAME%\%APP_NAME%.map" /Fo"apps\%APP_NAME%\%APP_NAME%.obj" /link /DLL /PDB:"apps\%APP_NAME%\%APP_NAME%.%TAG%.pdb" %COMMON_LINKER_FLAGS% "..\src\apps\%APP_NAME%\version.res"
cd ..
.\tools\pdb_path_fixer\pdb_path_fixer.exe ".\build\apps\%APP_NAME%\%APP_NAME%.dll"
robocopy .\build\apps\%APP_NAME% .\bin %APP_NAME%.*.pdb /xo /njh /njs /ndl /nc /ns
robocopy .\build\apps\%APP_NAME% .\bin %APP_NAME%.dll /xo /njh /njs /ndl /nc /ns
popd