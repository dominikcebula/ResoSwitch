#include "About.h"
#include "Version.h"
#include <string>
#include <Windows.h>
#include <CommCtrl.h>
#include <Shellapi.h>

static void SetWindowPosToCenterOfTheScreen(const HWND hDlg)
{
    RECT rcDlg;
    GetWindowRect(hDlg, &rcDlg);
    int dlgWidth = rcDlg.right - rcDlg.left;
    int dlgHeight = rcDlg.bottom - rcDlg.top;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int dlgX = (screenWidth - dlgWidth) / 2;
    int dlgY = (screenHeight - dlgHeight) / 2;
    SetWindowPos(hDlg, nullptr, dlgX, dlgY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

static std::wstring getLink(const HWND hDlg, int nIDDlgItem)
{
    wchar_t url[256] = {0};
    GetDlgItemText(hDlg, nIDDlgItem, url, 255);

    const wchar_t* start = wcsstr(url, L"<a>");
    const wchar_t* end = wcsstr(url, L"</a>");
    if (start && end && end > start)
    {
        start += 3;
        std::wstring link(start, end - start);

        return link;
    }

    return std::wstring{};
}

static INT_PTR CALLBACK AboutDlgProc(const HWND hDlg, const UINT message, const WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        {
            SetWindowPosToCenterOfTheScreen(hDlg);

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
    case WM_NOTIFY:
        {
            LPNMHDR pnmh = (LPNMHDR)lParam;

            if (pnmh->code == NM_CLICK && (pnmh->idFrom == IDC_SYSLINK_HOMEPAGE || pnmh->idFrom == IDC_SYSLINK_CONTACT))
            {
                std::wstring link = getLink(hDlg, pnmh->idFrom);
                if (pnmh->idFrom == IDC_SYSLINK_CONTACT)
                    link = L"mailto:" + link;

                ShellExecute(nullptr, L"open", link.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
            }
        }
        break;
    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    default:
        return FALSE;
    }
    return FALSE;
}

void ShowAboutDialog(const HWND hwnd)
{
    DialogBox(GetModuleHandle(nullptr), MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, AboutDlgProc);
}
