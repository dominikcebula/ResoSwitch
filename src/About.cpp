#include "About.h"
#include "Version.h"
#include <string>

void ShowAboutDialog(HWND hwnd)
{
    std::wstring about =
        std::wstring(L"ResoSwitch") +
        L"\nVersion: " + LoadAppVersion() +
        L"\nGit: https://github.com/dominikcebula/ResoSwitch" +
        L"\nAuthor: Dominik Cebula" +
        L"\nE-Mail: dominikcebula@gmail.com" +
        L"\nLicense: MIT License";
    MessageBox(hwnd, about.c_str(), L"About", MB_OK | MB_ICONINFORMATION);
}
