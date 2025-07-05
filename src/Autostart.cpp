#include "Autostart.h"

#include <string>
#include <Windows.h>

static const wchar_t* runKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
static const wchar_t* appName = L"ResoSwitch";

bool IsAutostartEnabled()
{
    HKEY hKey = nullptr;

    bool enabled = false;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        std::wstring exePath(MAX_PATH, L'\0');
        DWORD size = static_cast<DWORD>(exePath.size() * sizeof(wchar_t));
        const LONG result = RegQueryValueExW(hKey, appName, nullptr, nullptr, reinterpret_cast<LPBYTE>(&exePath[0]),
                                             &size);
        enabled = result == ERROR_SUCCESS;
        RegCloseKey(hKey);
    }
    return enabled;
}

void SetAutostart(bool enable)
{
    std::wstring exePath(MAX_PATH, L'\0');
    GetModuleFileNameW(nullptr, &exePath[0], static_cast<DWORD>(exePath.size()));
    exePath.resize(wcsnlen_s(exePath.c_str(), exePath.size()));
    HKEY hKey = nullptr;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, runKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
    {
        if (enable)
        {
            RegSetValueExW(hKey, appName, 0, REG_SZ, reinterpret_cast<const BYTE*>(exePath.c_str()),
                           static_cast<DWORD>((exePath.size() + 1) * sizeof(wchar_t)));
        }
        else
        {
            RegDeleteValueW(hKey, appName);
        }
        RegCloseKey(hKey);
    }
}
