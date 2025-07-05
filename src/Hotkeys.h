#pragma once

#include "Config.h"

#include <Windows.h>
#include <vector>

void RegisterResolutionHotkeys(HWND hwnd, const std::vector<ResolutionConfig>& resolutions);

void UnregisterResolutionHotkeys(HWND hwnd, size_t count);

bool ParseShortcut(const std::wstring& shortcut, HotkeyInfo& out);
