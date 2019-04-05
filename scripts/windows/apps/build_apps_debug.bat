cls
@echo off
set "ROOT=..\.."
set "APP_NAME=%1"
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
del bin\%APP_NAME%*.* /Q
del build\apps\%APP_NAME%*.* /Q
del build\apps\%APP_NAME%\%APP_NAME%* /Q
if not exist build mkdir build
cd build
if not exist apps mkdir apps
cd apps
if not exist %APP_NAME% mkdir %APP_NAME%
popd

call utctag
set TAG=%_utctag%

call log2 [info]
pushd %ROOT%
.\tools\bumpver\bumpver.exe -b ".\src\apps\%APP_NAME%\version.rc"
popd
echo.

call log [info] "Compiling %APP_NAME%.dll resources"
pushd %ROOT%
rc /d DEBUG ".\src\apps\%APP_NAME%\version.rc"
popd

call log [info] "Compiling %APP_NAME%"
pushd %ROOT%\build\apps
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% "%ROOT%\src\!windows\apps\%APP_NAME%\%APP_NAME%.windows.c" /Fe"%APP_NAME%\%APP_NAME%.dll" /Fm"%APP_NAME%\%APP_NAME%.map" /Fo"%APP_NAME%\%APP_NAME%.obj" /link /DLL /PDB:"%APP_NAME%\%APP_NAME%.%TAG%.pdb" %COMMON_LINKER_FLAGS% "%ROOT%\src\apps\%APP_NAME%\version.res"
popd
echo.

call log [info] "Fixing %APP_NAME%.dll pdb path"
pushd %ROOT%
.\tools\pdb_path_fixer\pdb_path_fixer.exe ".\build\apps\%APP_NAME%\%APP_NAME%.dll"
popd 
echo.

call log [info] "Copying output to bin"
pushd %ROOT%
robocopy .\build\apps\%APP_NAME% .\bin %APP_NAME%.*.pdb /xo /njh /njs /ndl /nc /ns /nfl
robocopy .\build\apps\%APP_NAME% .\bin %APP_NAME%.dll /xo /njh /njs /ndl /nc /ns /nfl
popd