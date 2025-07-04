#include "TrayMenu.h"
#include <wingdi.h>
#include <windows.h>
#include <strsafe.h>

constexpr UINT ID_TRAY_SHOW = 1001;
constexpr UINT ID_TRAY_ABOUT = 1002;
constexpr UINT ID_TRAY_EXIT = 1003;
constexpr UINT ID_TRAY_RES_BASE = 2000;

static HMENU hTrayMenu = nullptr;

void CreateTrayMenu(const std::vector<ResolutionConfig>& resolutions)
{
    hTrayMenu = CreatePopupMenu();
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        AppendMenuW(hTrayMenu, MF_STRING, ID_TRAY_RES_BASE + static_cast<UINT>(i), resolutions[i].label.c_str());
    }
    AppendMenu(hTrayMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hTrayMenu, MF_STRING, ID_TRAY_ABOUT, L"About");
    AppendMenu(hTrayMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hTrayMenu, MF_STRING, ID_TRAY_EXIT, L"Exit");
}

void ShowTrayMenu(const HWND hwnd)
{
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd);
    TrackPopupMenu(hTrayMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, nullptr);
}

void SetResolution(int width, int height)
{
    DEVMODE dm = {0};
    dm.dmSize = sizeof(dm);
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    LONG result = ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
    if (result != DISP_CHANGE_SUCCESSFUL)
    {
        MessageBox(nullptr, L"Failed to change resolution!", L"ResoSwitch - Error", MB_OK | MB_ICONERROR);
    }
}

void LoadAppVersion(wchar_t (&version)[64])
{
    swprintf_s(version, 64, L"Unknown");
    wchar_t exePath[MAX_PATH] = {0};
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

void ShowAboutDialog(HWND hwnd)
{
    wchar_t version[64];
    LoadAppVersion(version);
    wchar_t about[512];
    swprintf_s(
        about,
        L"ResoSwitch\nVersion: %s\nhttps://github.com/dominikcebula/ResoSwitch\nDominik Cebula\ndominikcebula@gmail.com",
        version);
    MessageBox(hwnd, about, L"About", MB_OK | MB_ICONINFORMATION);
}

void HandleMenuCommand(const HWND hwnd, const WPARAM wParam, const std::vector<ResolutionConfig>& resolutions)
{
    UINT id = LOWORD(wParam);
    if (id >= ID_TRAY_RES_BASE && id < ID_TRAY_RES_BASE + resolutions.size())
    {
        const auto& res = resolutions[id - ID_TRAY_RES_BASE];
        SetResolution(res.width, res.height);
        return;
    }
    switch (id)
    {
    case ID_TRAY_SHOW:
        MessageBox(hwnd, L"ResoSwitch is running!", L"Info", MB_OK | MB_ICONINFORMATION);
        break;
    case ID_TRAY_ABOUT:
        ShowAboutDialog(hwnd);
        break;
    case ID_TRAY_EXIT:
        PostQuitMessage(0);
        break;
    }
}

void DestroyTrayMenu()
{
    if (hTrayMenu)
    {
        DestroyMenu(hTrayMenu);
        hTrayMenu = nullptr;
    }
}
