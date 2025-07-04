#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include <windows.h>

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    constexpr wchar_t CLASS_NAME[] = L"TrayAppWindowClass";

    const HWND hwnd = CreateTrayAppWindow(hInstance, CLASS_NAME);
    if (!hwnd) return -1;

    // Register global hotkeys
    RegisterHotKey(hwnd, 1, MOD_CONTROL | MOD_SHIFT, '1'); // 720p
    RegisterHotKey(hwnd, 2, MOD_CONTROL | MOD_SHIFT, '2'); // 1080p
    RegisterHotKey(hwnd, 3, MOD_CONTROL | MOD_SHIFT, '3'); // 4k

    InitTrayIcon(hwnd);
    CreateTrayMenu();

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyTrayMenu();
    // Unregister hotkeys
    UnregisterHotKey(hwnd, 1);
    UnregisterHotKey(hwnd, 2);
    UnregisterHotKey(hwnd, 3);
    return 0;
}
