#pragma once
#include <string>
#include <vector>

struct ResolutionConfig
{
    std::wstring label;
    int width;
    int height;
    std::wstring shortcut;
};

std::wstring GetConfigFilePath();
bool LoadResolutionsFromIni(std::vector<ResolutionConfig>& resolutions);
void GenerateDefaultIniIfMissing();
