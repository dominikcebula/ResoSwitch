#include "About.h"
#include "Version.h"
#include <cstdio>

void ShowAboutDialog(HWND hwnd)
{
    wchar_t version[64];
    LoadAppVersion(version);
    wchar_t about[512];
    swprintf_s(
        about,
        L"ResoSwitch\nVersion: %s\nGit: https://github.com/dominikcebula/ResoSwitch\nAuthor: Dominik Cebula\nE-Mail: dominikcebula@gmail.com\nLicense: MIT License",
        version);
    MessageBox(hwnd, about, L"About", MB_OK | MB_ICONINFORMATION);
}
