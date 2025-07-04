#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include "Config.h"
#include <windows.h>
#include <map>

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    constexpr wchar_t CLASS_NAME[] = L"TrayAppWindowClass";

    // Generate default INI if missing
    GenerateDefaultIniIfMissing();
    std::vector<ResolutionConfig> resolutions;
    LoadResolutionsFromIni(resolutions);

    const HWND hwnd = CreateTrayAppWindow(hInstance, CLASS_NAME, &resolutions);
    if (!hwnd) return -1;

    // Register global hotkeys for each resolution
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        HotkeyInfo hk;
        if (ParseShortcut(resolutions[i].shortcut, hk) && hk.vk != 0)
        {
            RegisterHotKey(hwnd, (int)i + 1, hk.modifiers, hk.vk);
        }
    }

    InitTrayIcon(hwnd);
    CreateTrayMenu(resolutions);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyTrayMenu();
    // Unregister hotkeys
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        UnregisterHotKey(hwnd, (int)i + 1);
    }
    return 0;
}
