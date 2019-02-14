@echo off
call "%programfiles(x86)%\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall" x64
REM back to root
cd ..\..\
pushd bin
devenv sandbox.exe
popd
