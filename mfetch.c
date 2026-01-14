/*
Author: Joshua Manicom
Date: January 13th, 2026
Description: This is a CLI tool built to display system information using the C programming language. This was taken up as a project to learn
more C by using I/O, malloc, etc.
*/

#include <stdio.h>
#include <windows.h>

void printOS() {
    HKEY hKey;
    char product_name[256] = {0};
    char display_version[256] = {0};
    char current_build[256] = {0};
    DWORD buffer_size = sizeof(product_name);
    
    // Open the registry key where Windows stores version info
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, 
                      "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                      0, 
                      KEY_READ, 
                      &hKey) == ERROR_SUCCESS) {
        
        // Read ProductName (e.g., "Windows 11 Pro")
        RegQueryValueExA(hKey, "ProductName", NULL, NULL, (LPBYTE)product_name, &buffer_size);
        
        // Read DisplayVersion (e.g., "23H2")
        buffer_size = sizeof(display_version);
        RegQueryValueExA(hKey, "DisplayVersion", NULL, NULL, (LPBYTE)display_version, &buffer_size);
        
        // Read CurrentBuild
        buffer_size = sizeof(current_build);
        RegQueryValueExA(hKey, "CurrentBuild", NULL, NULL, (LPBYTE)current_build, &buffer_size);

        int build = atoi(current_build);
        if (build >= 22000) {
            // Find windows 10 and replace with 11
            char* pos = strstr(product_name, "Windows 10");
            if (pos != NULL) {
                // Copy everything after "Windows 10"
                char tmp[256];
                strcpy(tmp, pos + 10);
                strcpy(pos, "Windows 11");
                strcat(pos, tmp);
            }
        }
        
        printf("OS: %s %s (Build %s)\n", product_name, display_version, current_build);
        
        RegCloseKey(hKey);
    } else {
        printf("OS: Unable to read version info\n");
    }
}

void printInfo() {
    // Logo
    char* logo[] =  {
        "\033[034m            ___      _       _   \033[0m",
        "\033[034m      /\\/\\ /  _| ___| |_ ___| |__\033[0m",
        "\033[034m     /    \\| |_ / _ \\ __/ __| '_  \\ \033[0m",
        "\033[034m    / /\\/\\ \\  _|  __/ || (__| | | |\033[0m",
        "\033[034m    \\/    \\/_|  \\___|\\__\\___|_| |_|\033[0m",
        "",
        "",
        "",
        ""
    };

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

    // Create '=========' to length based on username + computername
    int seplen = strlen(username) + strlen(computername) + 1;
    char seperator[256];
    memset(seperator, '=', seplen);
    seperator[seplen] = '\0';

    // Information lines
    char info[8][256]; // Array of 8 strings, each up to 256 char

    sprintf(info[0], "\033[34m%s@%s\033[0m", username, computername);
    snprintf(info[1], 256, "%s", seperator);
    sprintf(info[2], "\033[1;36mOS:\033[0m Getting info...");
    sprintf(info[3], "\033[1;36m\033[0m");
    sprintf(info[4], "\033[1;36m\033[0m");
    sprintf(info[5], "\033[1;36m\033[0m");
    sprintf(info[6], "\033[1;36m\033[0m");
    sprintf(info[7], "\033[1;36m\033[0m");

    for (int i = 0; i < 8; i++) {
        printf("%-50s %s\n", logo[i], info[i]);
    }

}

int main()
{
    // Enable ANSI color codes
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    printInfo();

    return 0;
}