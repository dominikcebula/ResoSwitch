#include "TrayIcon.h"
#include <shellapi.h>

static NOTIFYICONDATA nid{};

void InitTrayIcon(const HWND hwnd)
{
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(GetModuleHandle(nullptr), L"IDI_ICON");
    wcscpy_s(nid.szTip, L"ResoSwitch");
    Shell_NotifyIcon(NIM_ADD, &nid);
}

void CleanupTrayIcon()
{
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
