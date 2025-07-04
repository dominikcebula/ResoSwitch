#include "TrayMenu.h"

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
        MessageBox(hwnd, L"Switching to 720p (placeholder)", L"Resolution", MB_OK | MB_ICONINFORMATION);
        break;
    case ID_TRAY_1080P:
        MessageBox(hwnd, L"Switching to 1080p (placeholder)", L"Resolution", MB_OK | MB_ICONINFORMATION);
        break;
    case ID_TRAY_4K:
        MessageBox(hwnd, L"Switching to 4k (placeholder)", L"Resolution", MB_OK | MB_ICONINFORMATION);
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
