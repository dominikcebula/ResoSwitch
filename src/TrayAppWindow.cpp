#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include "Config.h"
#include <vector>

static std::vector<ResolutionConfig>* g_resolutions = nullptr;

void SetResolutionsPtr(std::vector<ResolutionConfig>* resolutions)
{
    g_resolutions = resolutions;
}

LRESULT CALLBACK WndProc(const HWND hwnd, const UINT msg, const WPARAM wParam, const LPARAM lParam)
{
    switch (msg)
    {
    case WM_TRAYICON:
        if (lParam == WM_RBUTTONUP)
            ShowTrayMenu(hwnd);
        return 0;
    case WM_COMMAND:
        if (g_resolutions)
            HandleMenuCommand(hwnd, wParam, *g_resolutions);
        return 0;
    case WM_HOTKEY:
        if (g_resolutions && wParam >= 1 && wParam <= g_resolutions->size())
            HandleMenuCommand(hwnd, 2000 + (wParam - 1), *g_resolutions);
        return 0;
    case WM_DESTROY:
        CleanupTrayIcon();
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

HWND CreateTrayAppWindow(HINSTANCE hInstance, const wchar_t* className, std::vector<ResolutionConfig>* resolutions)
{
    SetResolutionsPtr(resolutions);
    WNDCLASS wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;
    RegisterClass(&wc);

    return CreateWindowEx(0, className, L"ResoSwitch", 0,
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          nullptr, nullptr, hInstance, nullptr);
}
