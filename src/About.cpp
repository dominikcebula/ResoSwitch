#include "About.h"
#include "Version.h"
#include <string>
#include <windows.h>

INT_PTR CALLBACK AboutDlgProc(const HWND hDlg, const UINT message, const WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        {
            const std::wstring version = LoadAppVersion();
            SetDlgItemText(hDlg, IDC_ABOUT_VERSION, version.c_str());
        }
        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;
    default:
        return FALSE;
    }
    return FALSE;
}

void ShowAboutDialog(const HWND hwnd)
{
    DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, AboutDlgProc);
}
