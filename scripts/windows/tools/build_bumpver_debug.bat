cls
@echo off

set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS"
set "WARNINGS=/wd4100 /wd4204 /wd4312 /wd4201 /wd4055 /wd4054"

set "COMMON_COMPILER_FLAGS=/MTd /nologo /Gm- /GR- /EHa- /Od /Oi %WARNINGS% /FC /Z7 %DEFINES%"
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
pushd p:\
del tools /Q
del tools\bumpver /Q
if not exist tools mkdir tools
cd tools
if not exist bumpver mkdir bumpver
cd ..
popd

call log [info] "Building bumpver.exe"
pushd p:\tools\bumpver
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% /Febumpver.exe "..\..\src\!windows\tools\bumpver\r_bumpver.windows.c" /link /subsystem:console %COMMON_LINKER_FLAGS%
popd