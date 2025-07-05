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

bool ParseShortcut(const std::wstring& shortcut, HotkeyInfo& out)
{
    out.modifiers = 0;
    out.vk = 0;
    std::wstring s = shortcut;
    for (auto& c : s) c = towupper(c);
    if (s.find(L"CTRL") != std::wstring::npos) out.modifiers |= MOD_CONTROL;
    if (s.find(L"SHIFT") != std::wstring::npos) out.modifiers |= MOD_SHIFT;
    if (s.find(L"ALT") != std::wstring::npos) out.modifiers |= MOD_ALT;
    if (s.find(L"WIN") != std::wstring::npos) out.modifiers |= MOD_WIN;

    size_t pos = s.rfind(L'+');
    std::wstring key = pos != std::wstring::npos ? s.substr(pos + 1) : s;
    if (key.length() == 1 && key[0] >= L'0' && key[0] <= L'9')
    {
        out.vk = '0' + (key[0] - L'0');
        return true;
    }
    if (key.length() == 1 && key[0] >= L'A' && key[0] <= L'Z')
    {
        out.vk = 'A' + (key[0] - L'A');
        return true;
    }

    return false;
}
