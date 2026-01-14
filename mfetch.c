/*
Author: Joshua Manicom
Date: January 13th, 2026
Description: This is a CLI tool built to display system information using the C programming language. This was taken up as a project to learn
more C by using I/O, malloc, etc.
*/

#include <stdio.h>
#include <windows.h>


void printLogo() {
    printf("\033[034m");  // Cyan color
    printf("            ___      _       _  \n");
    printf("      /\\/\\ /  _| ___| |_ ___| |__\n");
    printf("     /    \\| |_ / _ \\ __/ __| '_  \\ \n");
    printf("    / /\\/\\ \\  _|  __/ || (__| | | |\n");
    printf("    \\/    \\/_|  \\___|\\__\\___|_| |_|\n");
    printf("\033[0m");   // Reset color
}

int main()
{
    // Enable ANSI color codes
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    printLogo();
    printf("\n");

    // Create username variables
    char username[256];     // Create username buffer to hold string
    char computername[256]; // Create computername buffer to hold string

    // DWORD is a windows type, essentially 32-bit unsigned int
    DWORD username_len = sizeof(username);
    DWORD computername_len = sizeof(computername);

    // Username getters, both take input buffer and size of buffer

    // Get username
    GetUserNameA(username, &username_len);  // Passes address of username_len and WinAPI call modifies its value to the correct one
    
    // Get computername
    GetComputerNameA(computername, &computername_len);

    printf("%s@%s\n", username, computername);
    printf("\033[034m========================================\033[0m\n");

    return 0;
}