#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include "Config.h"
#include "Autostart.h"
#include <windows.h>
#include <map>
#include <vector>

void RegisterResolutionHotkeys(HWND hwnd, const std::vector<ResolutionConfig>& resolutions)
{
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        HotkeyInfo hk;
        if (ParseShortcut(resolutions[i].shortcut, hk) && hk.vk != 0)
        {
            RegisterHotKey(hwnd, static_cast<int>(i) + 1, hk.modifiers, hk.vk);
        }
    }
}

void UnregisterResolutionHotkeys(HWND hwnd, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        UnregisterHotKey(hwnd, static_cast<int>(i) + 1);
    }
}

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    constexpr wchar_t CLASS_NAME[] = L"TrayAppWindowClass";

    GenerateDefaultIniIfMissing();
    std::vector<ResolutionConfig> resolutions;
    LoadResolutionsFromIni(resolutions);

    SetAutostartMenuState(IsAutostartEnabled());

    const HWND hwnd = CreateTrayAppWindow(hInstance, CLASS_NAME, &resolutions);
    if (!hwnd) return -1;

    RegisterResolutionHotkeys(hwnd, resolutions);
    InitTrayIcon(hwnd);
    CreateTrayMenu(resolutions);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyTrayMenu();
    UnregisterResolutionHotkeys(hwnd, resolutions.size());
    return 0;
}
