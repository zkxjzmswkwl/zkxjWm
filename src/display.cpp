#include "display.h"
#include <Windows.h>

// In case this ever spits back garbage values, this is likely why.
// https://learn.microsoft.com/en-us/windows/win32/hidpi/high-dpi-desktop-application-development-on-windows
void display::refresh_resolution()
{
    RECT badtype;
    auto desktop = GetDesktopWindow();
    GetWindowRect(desktop, &badtype);
    m_resolution = vec2i(badtype.right, badtype.bottom);
}

vec2i *display::get_resolution() {
    return &m_resolution;
}
