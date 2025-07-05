#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include "Config.h"
#include "Autostart.h"
#include "Hotkeys.h"
#include <Windows.h>
#include <map>
#include <vector>

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
