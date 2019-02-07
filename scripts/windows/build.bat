@echo off
call "%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64
echo error: test
cd ..\..\
rmdir bin /s /q
del bin /s /q
mkdir bin
pushd bin
cl /Zi "..\src\windows\r_main.c" user32.lib
popd
