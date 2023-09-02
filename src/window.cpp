#include "window.h"
#include <iostream>

template class std::shared_ptr<window>;

window::window(HWND hwnd)
{
    this->m_hwnd = hwnd;
    store_current_title();
    store_current_position();
}

void window::store_current_position()
{
    RECT badtype;
    auto result = GetWindowRect(this->m_hwnd, &badtype);
    if (!result) {
        // 1400 = invalid hwnd
        printf("GetWindowRect(this->m_hwnd, &badtype) failed with error: %lu\n", GetLastError());
        return;
    }
    m_windowposition.width = badtype.right - badtype.left;
    m_windowposition.height = badtype.bottom - badtype.top;
    m_windowposition.x = badtype.left;
    m_windowposition.y = badtype.top;
}

void window::store_current_title()
{
    char buffer[256];
    GetWindowText(m_hwnd, buffer, 256);
    m_title = std::string(buffer);
}

void window::apply_position()
{
    MoveWindow(m_hwnd,
               m_windowposition.x,
               m_windowposition.y,
               m_windowposition.width,
               m_windowposition.height,
               TRUE);
}

std::shared_ptr<window> window::make(HWND hwnd)
{
	std::shared_ptr<window> windowptr = std::make_shared<window>(hwnd);
	return windowptr;
}

void window::set_position(int mode, int x, int y, int displaywidth, int displayheight)
{
    if (mode == CENTERED) {
        m_windowposition = vec4i(
            abs ( ( displaywidth / 2 ) - x / 2 ),
                abs ( ( displayheight  ) - y  ) / 2,
                x, y);
    }

    apply_position();
}

void window::unwindowsify()
{
    LONG style = GetWindowLong(m_hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU );
    SetWindowLong(m_hwnd, GWL_STYLE, style);
    // In order for the style change to take, we need to force a repaint of the window.
    // Refreshing the window's position does so, so long as `bRepaint` is true.
    apply_position();
}

/**
 * @param amount - will grow the window if amount is positive, shrink if negative.
 */
void window::resize_evenly(int amount)
{
    store_current_position();
    if (amount < 0) {
        amount = abs(amount);
        m_windowposition.width -= amount;
        m_windowposition.x = m_windowposition.x + (amount / 2);
    } else {
        m_windowposition.width += amount;
        m_windowposition.x = m_windowposition.x - (amount / 2);
    }
    apply_position();
}

























