#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"

LRESULT CALLBACK WndProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
    switch (msg)
    {
    case WM_TRAYICON:
        if (lParam == WM_RBUTTONUP)
            ShowTrayMenu(hwnd);
        return 0;
    case WM_COMMAND:
        HandleMenuCommand(hwnd, wParam);
        return 0;
    case WM_DESTROY:
        CleanupTrayIcon();
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

HWND CreateTrayAppWindow(HINSTANCE hInstance, const wchar_t* className)
{
    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClass(&wc);

    return CreateWindowEx(0, className, L"ResoSwitch", 0,
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          nullptr, nullptr, hInstance, nullptr);
}
