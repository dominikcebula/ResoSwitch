#include "TrayMenu.h"
#include <wingdi.h>

constexpr UINT ID_TRAY_SHOW = 1001;
constexpr UINT ID_TRAY_ABOUT = 1002;
constexpr UINT ID_TRAY_EXIT = 1003;
constexpr UINT ID_TRAY_720P = 1004;
constexpr UINT ID_TRAY_1080P = 1005;
constexpr UINT ID_TRAY_4K = 1006;

static HMENU hTrayMenu = nullptr;

void CreateTrayMenu()
{
    hTrayMenu = CreatePopupMenu();
    AppendMenu(hTrayMenu, MF_STRING, ID_TRAY_4K, L"4k");
    AppendMenu(hTrayMenu, MF_STRING, ID_TRAY_1080P, L"1080p");
    AppendMenu(hTrayMenu, MF_STRING, ID_TRAY_720P, L"720p");
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
        MessageBox(nullptr, L"Failed to change resolution!", L"Error", MB_OK | MB_ICONERROR);
    }
}

void HandleMenuCommand(const HWND hwnd, const WPARAM wParam)
{
    switch (LOWORD(wParam))
    {
    case ID_TRAY_SHOW:
        MessageBox(hwnd, L"ResoSwitch is running!", L"Info", MB_OK | MB_ICONINFORMATION);
        break;
    case ID_TRAY_ABOUT:
        MessageBox(
            hwnd, L"ResoSwitch\nhttps://github.com/dominikcebula/ResoSwitch\nDominik Cebula\ndominikcebula@gmail.com",
            L"About", MB_OK | MB_ICONINFORMATION);
        break;
    case ID_TRAY_720P:
        SetResolution(1280, 720);
        break;
    case ID_TRAY_1080P:
        SetResolution(1920, 1080);
        break;
    case ID_TRAY_4K:
        SetResolution(3840, 2160);
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
