#include <cstdio>
#include <vector>
#include <windows.h>

void LoadAppVersion(wchar_t (&version)[64])
{
    swprintf_s(version, 64, L"Unknown");
    wchar_t exePath[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    DWORD handle = 0;
    DWORD size = GetFileVersionInfoSizeW(exePath, &handle);
    if (size > 0)
    {
        std::vector<BYTE> data(size);
        if (GetFileVersionInfoW(exePath, handle, size, data.data()))
        {
            VS_FIXEDFILEINFO* fileInfo = nullptr;
            UINT len = 0;
            if (VerQueryValueW(data.data(), L"\\", reinterpret_cast<LPVOID*>(&fileInfo), &len) && fileInfo)
            {
                swprintf_s(version, 64, L"%d.%d.%d.%d",
                           HIWORD(fileInfo->dwFileVersionMS), LOWORD(fileInfo->dwFileVersionMS),
                           HIWORD(fileInfo->dwFileVersionLS), LOWORD(fileInfo->dwFileVersionLS));
            }
        }
    }
}
