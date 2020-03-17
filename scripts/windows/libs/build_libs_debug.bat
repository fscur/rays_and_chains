cls
@echo off
set "ROOT=..\..\.."
set "LIB_NAME=%1"
set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS /DGLFW_INCLUDE_NONE /DCIMGUI_DEFINE_ENUMS_AND_STRUCTS /DIMGUI_IMPL_OPENGL_LOADER_GLAD"
set "WARNINGS=/WX /W4 /wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054"

set "COMMON_COMPILER_FLAGS=/MT /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
set "INCLUDE_DIRS=/I%ROOT%\src /I%ROOT%\inc"
set "COMMON_LINKER_FLAGS=-opt:ref /LIBPATH:%ROOT%\lib\windows\debug"

call log [info] "DEBUG"
echo.

pushd %ROOT%
del bin\libs\%LIB_NAME%* /Q
del build\libs\%LIB_NAME%\*.* /Q

if not exist build mkdir build
cd build
if not exist windows mkdir windows
cd windows
if not exist libs mkdir libs
cd libs
if not exist %LIB_NAME% mkdir %LIB_NAME%
popd

call utctag
set TAG=%_utctag%

call log2 [info]
pushd %ROOT%
.\tools\bumpver\bumpver.exe -b ".\src\libs\%LIB_NAME%\version.rc"
popd
echo.

call log [info] "Compiling %LIB_NAME%.dll resources"
pushd p:\
rc /d DEBUG ".\src\libs\%LIB_NAME%\version.rc"
popd
echo.

call log [info] "Compiling %LIB_NAME%"
pushd %ROOT%\build\windows\libs\
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% "%ROOT%\src\libs\%LIB_NAME%\%LIB_NAME%.windows.c" /Fe"%LIB_NAME%\%LIB_NAME%.dll" /Fm"%LIB_NAME%\%LIB_NAME%.map" /Fo"%LIB_NAME%\%LIB_NAME%.obj" /link /DLL /PDB:"%LIB_NAME%\%LIB_NAME%.%TAG%.pdb" %COMMON_LINKER_FLAGS% "%ROOT%\src\libs\%LIB_NAME%\version.res"
popd
echo. 

call log [info] "Fixing %LIB_NAME%.dll pdb path"
pushd %ROOT%\
.\tools\pdb_path_fixer\pdb_path_fixer.exe ".\build\windows\libs\%LIB_NAME%\%LIB_NAME%.dll"
popd 

call log [info] "Copying output to bin"
pushd p:\
robocopy .\build\windows\libs\%LIB_NAME% .\bin\windows\libs %LIB_NAME%.*.pdb /xo /njh /njs /ndl /nc /ns /nfl
robocopy .\build\windows\libs\%LIB_NAME% .\bin\windows\libs %LIB_NAME%.dll /xo /njh /njs /ndl /nc /ns /nfl
popd