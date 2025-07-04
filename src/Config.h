#pragma once
#include <string>
#include <vector>
#include <windows.h>

struct ResolutionConfig
{
    std::wstring label;
    int width;
    int height;
    std::wstring shortcut;
};

struct HotkeyInfo
{
    UINT modifiers;
    UINT vk;
};

std::wstring GetConfigFilePath();
bool LoadResolutionsFromIni(std::vector<ResolutionConfig>& resolutions);
void GenerateDefaultIniIfMissing();
bool ParseShortcut(const std::wstring& shortcut, HotkeyInfo& out);
