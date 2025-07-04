#pragma once
#include <windows.h>

constexpr UINT WM_TRAYICON = WM_USER + 1;

void InitTrayIcon(HWND hwnd);
void CleanupTrayIcon();
