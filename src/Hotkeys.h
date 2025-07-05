#pragma once

#include "Config.h"

#include <windows.h>
#include <vector>

void RegisterResolutionHotkeys(HWND hwnd, const std::vector<ResolutionConfig>& resolutions);

void UnregisterResolutionHotkeys(HWND hwnd, size_t count);

bool ParseShortcut(const std::wstring& shortcut, HotkeyInfo& out);
