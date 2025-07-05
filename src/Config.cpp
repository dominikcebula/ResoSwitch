#include "Config.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <fstream>
#include <sstream>

std::wstring GetConfigFilePath()
{
    std::wstring exePath(MAX_PATH, L'\0');
    GetModuleFileNameW(nullptr, &exePath[0], static_cast<DWORD>(exePath.size()));
    PathRemoveExtensionW(&exePath[0]);
    exePath.resize(wcsnlen_s(exePath.c_str(), exePath.size()));
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
    std::wstring sectionNames(4096, L'\0');
    GetPrivateProfileSectionNamesW(&sectionNames[0], 4096, iniPath.c_str());
    for (const wchar_t* section = sectionNames.c_str(); *section; section += wcsnlen_s(section, 4096) + 1)
    {
        ResolutionConfig config;
        config.label.resize(128);
        GetPrivateProfileStringW(section, L"label", section, &config.label[0], 128, iniPath.c_str());
        config.label.resize(wcsnlen_s(config.label.c_str(), 128));
        config.width = GetPrivateProfileIntW(section, L"width", 0, iniPath.c_str());
        config.height = GetPrivateProfileIntW(section, L"height", 0, iniPath.c_str());
        config.shortcut.resize(64);
        GetPrivateProfileStringW(section, L"shortcut", L"", &config.shortcut[0], 64, iniPath.c_str());
        config.shortcut.resize(wcsnlen_s(config.shortcut.c_str(), 64));
        if (!config.label.empty() && config.width > 0 && config.height > 0)
        {
            resolutions.push_back(config);
        }
    }
    return !resolutions.empty();
}
