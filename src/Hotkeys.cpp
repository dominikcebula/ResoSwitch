#include "Hotkeys.h"

void RegisterResolutionHotkeys(HWND hwnd, const std::vector<ResolutionConfig>& resolutions)
{
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        HotkeyInfo hk = {};
        if (ParseShortcut(resolutions[i].shortcut, hk) && hk.vk != 0)
        {
            RegisterHotKey(hwnd, static_cast<int>(i) + 1, hk.modifiers, hk.vk);
        }
    }
}

void UnregisterResolutionHotkeys(HWND hwnd, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        UnregisterHotKey(hwnd, static_cast<int>(i) + 1);
    }
}
