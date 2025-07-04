#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include <windows.h>

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    constexpr wchar_t CLASS_NAME[] = L"TrayAppWindowClass";

    const HWND hwnd = CreateTrayAppWindow(hInstance, CLASS_NAME);
    if (!hwnd) return -1;

    InitTrayIcon(hwnd);
    CreateTrayMenu();

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyTrayMenu();
    return 0;
}
