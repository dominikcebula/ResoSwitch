#include <cstdio>
#include <vector>
#include <Windows.h>
#include <string>

std::wstring LoadAppVersion()
{
    std::wstring version = L"Unknown";
    std::wstring exePath(MAX_PATH, L'\0');
    GetModuleFileNameW(nullptr, &exePath[0], static_cast<DWORD>(exePath.size()));
    exePath.resize(wcsnlen_s(exePath.c_str(), exePath.size()));
    DWORD handle = 0;
    if (DWORD size = GetFileVersionInfoSizeW(exePath.c_str(), &handle); size > 0)
    {
        std::vector<BYTE> data(size);
        if (GetFileVersionInfoW(exePath.c_str(), handle, size, data.data()))
        {
            VS_FIXEDFILEINFO* fileInfo = nullptr;
            UINT len = 0;
            if (VerQueryValueW(data.data(), L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &len) && fileInfo)
            {
                wchar_t verBuf[64];
                swprintf_s(verBuf, 64, L"%d.%d.%d.%d",
                           HIWORD(fileInfo->dwFileVersionMS), LOWORD(fileInfo->dwFileVersionMS),
                           HIWORD(fileInfo->dwFileVersionLS), LOWORD(fileInfo->dwFileVersionLS));
                version = verBuf;
            }
        }
    }
    return version;
}
