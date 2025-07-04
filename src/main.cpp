#include "TrayAppWindow.h"
#include "TrayIcon.h"
#include "TrayMenu.h"
#include "Config.h"
#include <windows.h>
#include <map>

struct HotkeyInfo
{
    UINT modifiers;
    UINT vk;
};

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
    // Find the last '+' and get the key after it
    size_t pos = s.rfind(L'+');
    std::wstring key = (pos != std::wstring::npos) ? s.substr(pos + 1) : s;
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
    // Add more keys as needed
    return false;
}

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, PWSTR, int)
{
    constexpr wchar_t CLASS_NAME[] = L"TrayAppWindowClass";

    // Generate default INI if missing
    GenerateDefaultIniIfMissing();
    std::vector<ResolutionConfig> resolutions;
    LoadResolutionsFromIni(resolutions);

    const HWND hwnd = CreateTrayAppWindow(hInstance, CLASS_NAME, &resolutions);
    if (!hwnd) return -1;

    // Register global hotkeys for each resolution
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        HotkeyInfo hk;
        if (ParseShortcut(resolutions[i].shortcut, hk) && hk.vk != 0)
        {
            RegisterHotKey(hwnd, (int)i + 1, hk.modifiers, hk.vk);
        }
    }

    InitTrayIcon(hwnd);
    CreateTrayMenu(resolutions);

    MSG msg{};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyTrayMenu();
    // Unregister hotkeys
    for (size_t i = 0; i < resolutions.size(); ++i)
    {
        UnregisterHotKey(hwnd, (int)i + 1);
    }
    return 0;
}
