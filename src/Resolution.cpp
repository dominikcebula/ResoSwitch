#include "Resolution.h"

#include <string>
#include <Windows.h>

static std::wstring getErrorMessage(LONG result)
{
    switch (result)
    {
    case DISP_CHANGE_BADDUALVIEW:
        return L"The system is DualView capable. Settings change unsuccessful.";
    case DISP_CHANGE_BADFLAGS:
        return L"An invalid set of flags was passed in.";
    case DISP_CHANGE_BADMODE:
        return L"The graphics mode is not supported.";
    case DISP_CHANGE_BADPARAM:
        return L"An invalid parameter or flag was passed in.";
    case DISP_CHANGE_FAILED:
        return L"The display driver failed the specified graphics mode.";
    case DISP_CHANGE_NOTUPDATED:
        return L"Unable to write settings to the registry.";
    case DISP_CHANGE_RESTART:
        return L"The computer must be restarted for the graphics mode to work.";
    default:
        return L"Unknown error occurred while changing resolution.";
    }
}

void SetResolution(int width, int height)
{
    DEVMODE dm = {};
    dm.dmSize = sizeof(dm);
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    LONG result = ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
    if (result != DISP_CHANGE_SUCCESSFUL)
    {
        const std::wstring errorMsg = getErrorMessage(result);

        MessageBox(nullptr, std::wstring(L"Failed to change resolution: ").append(errorMsg).c_str(),
                   L"Error",
                   MB_OK | MB_ICONERROR);
    }
}
