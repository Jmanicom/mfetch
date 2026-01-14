@echo off

REM check if bin folder exists, if not create it
if not exist "%USERPROFILE%\bin\" (
    echo Creating bin folder...
    mkdir "%USERPROFILE%\bin"

    REM Add to PATH permanently (User PATH)
    echo Adding bin foler to PATH
    setx PATH "%PATH%;%USERPROFILE%\bin"
    echo NOTE: Restart terminal for PATH change to take effect
)

REM compile
gcc mfetch.c -o mfetch.exe

if %errorlevel% equ 0 (
    echo Build successful!
    copy mfetch.exe %USERPROFILE%\bin\ >nul 2>&1
    copy mfetch.exe %USERPROFILE%\msys64\ucrt64\bin >nul 2>&1
    mfetch.exe
)   else (
    echo Build failed!
)