@echo off
gcc mfetch.c -o mfetch.exe
if %errorlevel% equ 0 (
    echo Build successful!
    mfetch.exe
)   else (
    echo Build failed!
)