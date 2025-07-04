#pragma once
#include <windows.h>

constexpr UINT ID_TRAY_720P = 1004;
constexpr UINT ID_TRAY_1080P = 1005;
constexpr UINT ID_TRAY_4K = 1006;

void CreateTrayMenu();
void ShowTrayMenu(HWND hwnd);
void HandleMenuCommand(HWND hwnd, WPARAM wParam);
void DestroyTrayMenu();
