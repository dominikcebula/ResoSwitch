#include "Resolution.h"

#include <Windows.h>

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
        MessageBox(nullptr, L"Failed to change resolution!", L"ResoSwitch - Error", MB_OK | MB_ICONERROR);
    }
}
