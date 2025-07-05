#include "TrayMenu.h"
#include <wingdi.h>
#include <Windows.h>
#include <strsafe.h>

#include "Autostart.h"
#include "About.h"
#include "Resolution.h"

constexpr UINT ID_TRAY_SHOW = 1001;
constexpr UINT ID_TRAY_ABOUT = 1002;
constexpr UINT ID_TRAY_EXIT = 1003;
constexpr UINT ID_TRAY_AUTOSTART = 1004;
constexpr UINT ID_TRAY_RES_BASE = 2000;

static HMENU hTrayMenu = nullptr;
static bool g_isAutostartEnabled = false;

void CreateTrayMenu(const std::vector<ResolutionConfig>& resolutions)
{
    hTrayMenu = CreatePopupMenu();
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        AppendMenuW(hTrayMenu, MF_STRING, ID_TRAY_RES_BASE + static_cast<UINT>(i), resolutions[i].label.c_str());
    }
    AppendMenu(hTrayMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hTrayMenu, MF_STRING | (g_isAutostartEnabled ? MF_CHECKED : MF_UNCHECKED), ID_TRAY_AUTOSTART,
               L"Autostart");
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

void SetAutostartMenuState(bool enabled)
{
    g_isAutostartEnabled = enabled;
    if (hTrayMenu)
    {
        CheckMenuItem(hTrayMenu, ID_TRAY_AUTOSTART, MF_BYCOMMAND | (enabled ? MF_CHECKED : MF_UNCHECKED));
    }
}

bool HandleResolutionChange(const std::vector<ResolutionConfig>& resolutions, UINT id)
{
    if (id >= ID_TRAY_RES_BASE && id < ID_TRAY_RES_BASE + resolutions.size())
    {
        const auto& res = resolutions[id - ID_TRAY_RES_BASE];
        SetResolution(res.width, res.height);
        return true;
    }
    return false;
}

void HandleMenuCommand(const HWND hwnd, const WPARAM wParam, const std::vector<ResolutionConfig>& resolutions)
{
    UINT id = LOWORD(wParam);
    if (HandleResolutionChange(resolutions, id))
        return;
    switch (id)
    {
    case ID_TRAY_AUTOSTART:
        g_isAutostartEnabled = !g_isAutostartEnabled;
        SetAutostart(g_isAutostartEnabled);
        SetAutostartMenuState(g_isAutostartEnabled);
        break;
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
