cls
@echo off

set "DEFINES=/DUNICODE /D_DEBUG /DWIN32 /D_CRT_SECURE_NO_WARNINGS"
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
del bin\plugins\plugin_a* /Q
if not exist bin mkdir bin
cd bin
if not exist plugins mkdir plugins
popd

call log [info] "Building plugin_a.dll"

call utctag
set TAG=%_utctag%

call log2 [info]
pushd p:\
.\tools\bumpver\bumpver.exe -b ".\src\plugins\plugin_a\version.rc"
popd

pushd p:\
rc /d DEBUG ".\src\plugins\plugin_a\version.rc"
cd bin
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% "..\src\plugins\plugin_a\plugin_a.c" /Fe"plugins\plugin_a.dll" /Fm"plugins\plugin_a.map" /Fo"plugins\plugin_a.obj" /link /DLL /PDB:"plugins\plugin_a.%TAG%.pdb" %COMMON_LINKER_FLAGS% "..\src\plugins\plugin_a\version.res"
cd ..
.\tools\pdb_path_fixer\pdb_path_fixer.exe ".\bin\plugins\plugin_a.dll"
popd