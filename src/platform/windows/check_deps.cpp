#include <string>
#include <windows.h>

bool CheckRegistry(HKEY hKeyRoot, LPCSTR subKey, LPCSTR displayNameToFind)
{
    HKEY hKey;
    if (RegOpenKeyExA(hKeyRoot, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        return false;
    }

    char keyName[256];
    DWORD keyNameSize = sizeof(keyName);
    DWORD index = 0;

    while (RegEnumKeyExA(hKey, index++, keyName, &keyNameSize, NULL, NULL, NULL,
                         NULL) == ERROR_SUCCESS) {
        HKEY appKey;
        if (RegOpenKeyExA(hKey, keyName, 0, KEY_READ, &appKey) ==
            ERROR_SUCCESS) {
            char displayName[256];
            DWORD displayNameSize = sizeof(displayName);
            if (RegQueryValueExA(appKey, "DisplayName", NULL, NULL,
                                 (LPBYTE)displayName,
                                 &displayNameSize) == ERROR_SUCCESS) {
                if (strcmp(displayName, displayNameToFind) == 0) {
                    RegCloseKey(appKey);
                    RegCloseKey(hKey);
                    return true;
                }
            }
            RegCloseKey(appKey);
        }
        keyNameSize = sizeof(keyName);
    }

    RegCloseKey(hKey);
    return false;
}

bool IsAppleMobileDeviceSupportInstalled()
{
    if (CheckRegistry(HKEY_LOCAL_MACHINE,
                      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
                      "Apple Mobile Device Support")) {
        return true;
    }
    if (CheckRegistry(HKEY_LOCAL_MACHINE,
                      "SOFTWARE\\WOW6432Node\\Microsoft\\Wi"
                      "ndows\\CurrentVersion\\Uninstall",
                      "Apple Mobile Device Support")) {
        return true;
    }
    return false;
}

bool IsWinFspInstalled()
{
    if (CheckRegistry(HKEY_LOCAL_MACHINE,
                      "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall",
                      "WinFsp 2025")) {
        return true;
    }
    if (CheckRegistry(HKEY_LOCAL_MACHINE,
                      "SOFTWARE\\WOW6432Node\\Microsoft\\Wi"
                      "ndows\\CurrentVersion\\Uninstall",
                      "WinFsp 2025")) {
        return true;
    }
    return false;
}