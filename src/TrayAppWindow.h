#pragma once
#include <Windows.h>
#include <vector>
#include "Config.h"

HWND CreateTrayAppWindow(HINSTANCE hInstance, const wchar_t* className, std::vector<ResolutionConfig>* resolutions);
