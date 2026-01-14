/*
Author: Joshua Manicom
Date: January 13th, 2026
Description: This is a CLI tool built to display system information using the C programming language. This was taken up as a project to learn
more C by using I/O, malloc, etc.
*/

#include <stdio.h>
#include <windows.h>

void getOSinfo(char* buffer, size_t size) {
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
        
        snprintf(buffer, size, "%s %s (Build %s)", product_name, display_version, current_build);
        RegCloseKey(hKey);
    } else {
        snprintf(buffer, size, "Uknown");
    }
}

void getCPUinfo(char* buffer, size_t size)
{
    HKEY hKey;
    char CPUName[256] = {0};
    DWORD buffer_size = sizeof(CPUName);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExA(hKey, "ProcessorNameString", NULL, NULL, (LPBYTE)CPUName, &buffer_size);

        snprintf(buffer, size, "%s", CPUName);
        RegCloseKey(hKey);
    } else {
        snprintf(buffer, size, "Unknown");
    }
}

void getRAMinfo(char* buffer, size_t size)
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);

    // Convert bytes to MiB
    unsigned long long totalMiB = statex.ullTotalPhys / (1024 * 1024);
    unsigned long long usedMiB = (statex.ullTotalPhys - statex.ullAvailPhys) / (1024 * 1024);

    snprintf(buffer, size, "%lluMiB / %lluMiB", usedMiB, totalMiB);
}

void getUptime(char* buffer, size_t size) 
{
    ULONGLONG uptime_ms = GetTickCount64();

    // Convert ms to days, hours, minutes
    int days = uptime_ms / (1000 * 60 * 60 * 24);
    int hours = uptime_ms / (1000 * 60 * 60) % 24;
    int mins = uptime_ms / (1000 * 60) % 60;

    if (days > 0) {
        snprintf(buffer, size, "%d days, %d hours, %d mins", days, hours, mins);
    } else if (hours > 0) {
        snprintf(buffer, size, "%d hours, %d mins", hours, mins);
    } else {
        snprintf(buffer, size, "%d mins", mins);
    }
}

void printInfo() {
    // Logo
    char* logo[] =  {
        "            ___      _       _   ",
        "      /\\/\\ /  _| ___| |_ ___| |__",
        "     /    \\| |_ / _ \\ __/ __| '_  \\",
        "    / /\\/\\ \\  _|  __/ || (__| | | |",
        "    \\/    \\/_|  \\___|\\__\\___|_| |_|",
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

    // Information lines
    char info[8][256] = {0}; // Array of 8 strings, each up to 256 char

    // Create '=========' to length based on username + computername
    int seplen = strlen(username) + strlen(computername) + 1;
    char seperator[256];
    memset(seperator, '=', seplen);
    seperator[seplen] = '\0';

    // Get OS information
    char OSinfo[256];
    getOSinfo(OSinfo, sizeof(OSinfo));

    // Get CPU info
    char CPUinfo[256];
    getCPUinfo(CPUinfo, sizeof(CPUinfo));

    // Get RAM info
    char RAMinfo[256];
    getRAMinfo(RAMinfo, sizeof(RAMinfo));

    // Get uptime info
    char Uptime[256];
    getUptime(Uptime, sizeof(Uptime));

    // Print information lines out
    snprintf(info[0], username_len + computername_len, "\033[34m%s@%s\033[0m", username, computername);
    snprintf(info[1], 256, "%s", seperator);
    sprintf(info[2], "\033[1;32mOS:\033[0m %s", OSinfo);
    sprintf(info[3], "\033[1;32mUptime:\033[0m %s", Uptime);
    sprintf(info[4], "\033[1;32mCPU:\033[0m %s", CPUinfo);
    sprintf(info[5], "\033[1;32mRAM:\033[0m %s", RAMinfo);
    sprintf(info[6], "\033[1;32m\033[0m");
    sprintf(info[7], "\033[1;32m\033[0m");

    for (int i = 0; i < 8; i++) {
        printf("\033[1;34m%-40s\033[0m    %s\n", logo[i], info[i]);
        Sleep(75);
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