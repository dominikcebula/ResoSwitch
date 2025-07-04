#pragma once
#include <windows.h>
#include <vector>
#include "Config.h"

void CreateTrayMenu(const std::vector<ResolutionConfig>& resolutions);
void ShowTrayMenu(HWND hwnd);
void HandleMenuCommand(HWND hwnd, WPARAM wParam, const std::vector<ResolutionConfig>& resolutions);
void DestroyTrayMenu();
