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
del bin\plugins\plugin_b*.* /Q
del bin\plugins\plugin_b\plugin_b* /Q
if not exist bin mkdir bin
cd bin
if not exist plugins mkdir plugins
cd plugins
if not exist plugin_b mkdir plugin_b
popd

call log [info] "Building plugin_b.dll"

call utctag
set TAG=%_utctag%

call log2 [info]
pushd p:\
.\tools\bumpver\bumpver.exe -b ".\src\plugins\plugin_b\version.rc"
popd

call log [info] "Compiling plugin_b.dll resources"
pushd p:\
rc /d DEBUG ".\src\plugins\plugin_b\version.rc"
cd bin
cl %INCLUDE_DIRS% %COMMON_COMPILER_FLAGS% "..\src\plugins\plugin_b\plugin_b.c" /Fe"plugins\plugin_b\plugin_b.dll" /Fm"plugins\plugin_b\plugin_b.map" /Fo"plugins\plugin_b\plugin_b.obj" /link /DLL /PDB:"plugins\plugin_b\plugin_b.%TAG%.pdb" %COMMON_LINKER_FLAGS% "..\src\plugins\plugin_b\version.res"
cd ..
.\tools\pdb_path_fixer\pdb_path_fixer.exe ".\bin\plugins\plugin_b\plugin_b.dll"
robocopy .\bin\plugins\plugin_b .\bin\plugins plugin_b.*.pdb /xo /njh /njs /ndl /nc /ns
robocopy .\bin\plugins\plugin_b .\bin\plugins plugin_b.dll /xo /njh /njs /ndl /nc /ns
popd