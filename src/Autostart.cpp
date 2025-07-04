#include "Autostart.h"
#include <windows.h>

static const wchar_t* runKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
static const wchar_t* appName = L"ResoSwitch";

bool IsAutostartEnabled()
{
    HKEY hKey = nullptr;

    bool enabled = false;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        wchar_t exePath[MAX_PATH];
        DWORD size = sizeof(exePath);
        LONG result = RegQueryValueExW(hKey, appName, nullptr, nullptr, reinterpret_cast<LPBYTE>(exePath), &size);
        enabled = (result == ERROR_SUCCESS);
        RegCloseKey(hKey);
    }
    return enabled;
}

void SetAutostart(bool enable)
{
    wchar_t exePath[MAX_PATH] = {0};
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    HKEY hKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        if (enable)
        {
            RegSetValueExW(hKey, appName, 0, REG_SZ, reinterpret_cast<const BYTE*>(exePath),
                           static_cast<DWORD>((wcslen(exePath) + 1) * sizeof(wchar_t)));
        }
        else
        {
            RegDeleteValueW(hKey, appName);
        }
        RegCloseKey(hKey);
    }
}
