#pragma once
#include <windows.h>

void CreateTrayMenu();
void ShowTrayMenu(HWND hwnd);
void HandleMenuCommand(HWND hwnd, WPARAM wParam);
void DestroyTrayMenu();
