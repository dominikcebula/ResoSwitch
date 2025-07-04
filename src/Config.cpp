#include "Config.h"
#include <windows.h>
#include <shlwapi.h>
#include <fstream>
#include <sstream>

std::wstring GetConfigFilePath()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    PathRemoveExtensionW(exePath);
    std::wstring iniPath = exePath;
    iniPath += L".ini";
    return iniPath;
}

void GenerateDefaultIniIfMissing()
{
    std::wstring iniPath = GetConfigFilePath();
    std::ifstream iniStream(iniPath);
    if (iniStream.good()) return;
    iniStream.close();
    std::wofstream iniOutputStream(iniPath);
    iniOutputStream << L"[4k]\nlabel=4k\nwidth=3840\nheight=2160\nshortcut=CTRL+SHIFT+3\n\n";
    iniOutputStream << L"[1080p]\nlabel=1080p\nwidth=1920\nheight=1080\nshortcut=CTRL+SHIFT+2\n\n";
    iniOutputStream << L"[720p]\nlabel=720p\nwidth=1280\nheight=720\nshortcut=CTRL+SHIFT+1\n\n";
    iniOutputStream.close();
}

bool LoadResolutionsFromIni(std::vector<ResolutionConfig>& resolutions)
{
    std::wstring iniPath = GetConfigFilePath();
    wchar_t sectionNames[4096] = {};
    GetPrivateProfileSectionNamesW(sectionNames, 4096, iniPath.c_str());
    for (wchar_t* section = sectionNames; *section; section += wcslen(section) + 1)
    {
        ResolutionConfig config;
        config.label.resize(128);
        GetPrivateProfileStringW(section, L"label", section, &config.label[0], 128, iniPath.c_str());
        config.label.resize(wcslen(config.label.c_str()));
        config.width = GetPrivateProfileIntW(section, L"width", 0, iniPath.c_str());
        config.height = GetPrivateProfileIntW(section, L"height", 0, iniPath.c_str());
        config.shortcut.resize(64);
        GetPrivateProfileStringW(section, L"shortcut", L"", &config.shortcut[0], 64, iniPath.c_str());
        config.shortcut.resize(wcslen(config.shortcut.c_str()));
        if (!config.label.empty() && config.width > 0 && config.height > 0)
        {
            resolutions.push_back(config);
        }
    }
    return !resolutions.empty();
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
