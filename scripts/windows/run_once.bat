cls
@echo off
subst p: /D
taskkill /f /im nav.exe
del ahk-install.exe /q /f
del nav.exe /q /f
del nav.ahk /q /f
echo Download Autohotkey
powershell -Command "Invoke-WebRequest https://www.autohotkey.com/download/ahk-install.exe -OutFile ahk-install.exe"
echo Install Autohotkey
ahk-install.exe /S
echo Create nav.ahk
echo SendMode Input >> nav.ahk
echo SetWorkingDir %%A_ScriptDir%% >> nav.ahk
echo !j:: >> nav.ahk
echo Send, {Left} >> nav.ahk
echo return >> nav.ahk
echo !l:: >> nav.ahk
echo Send, {Right} >> nav.ahk
echo return >> nav.ahk
echo !k:: >> nav.ahk
echo Send, {Down} >> nav.ahk
echo return >> nav.ahk
echo !i:: >> nav.ahk
echo Send, {Up} >> nav.ahk
echo return >> nav.ahk
echo !u:: >> nav.ahk
echo Send, {Home} >> nav.ahk
echo return >> nav.ahk
echo !o:: >> nav.ahk
echo Send, {End} >> nav.ahk
echo return >> nav.ahk
echo Compile nav.ahk
"%programfiles%\AutoHotkey\Compiler\Ahk2Exe.exe" /in nav.ahk
echo Copy nav.exe to StartUp
xcopy nav.exe "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup" /y
pushd "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup
start nav.exe
popd
echo Copy run_startup.bat to StartUp
xcopy run_on_startup.bat "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup" /y
pushd "%appdata%\Microsoft\Windows\Start Menu\Programs\Startup"
call run_on_startup.bat
popd
echo Cleanup
del ahk-install.exe /q /f
del nav.exe /q /f
del nav.ahk /q /f
explorer.exe p:\