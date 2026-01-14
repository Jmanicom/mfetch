@echo off
gcc mfetch.c -o mfetch.exe
if %errorlevel% equ 0 (
    echo Build successful!
    copy mfetch.exe %USERPROFILE%\bin\ >nul 2>&1
    copy mfetch.exe %USERPROFILE%\msys64\ucrt64\bin >nul 2>&1
    mfetch.exe
)   else (
    echo Build failed!
)