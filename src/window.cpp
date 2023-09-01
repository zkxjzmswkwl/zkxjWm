#include "window.h"
#include <iostream>

template class std::shared_ptr<window>;

window::window()
{
    m_windowposition = vec4i{ 1, 1, 1, 1 } ;
}

window::window(HWND hwnd)
{
    this->m_hwnd = hwnd;
}

void window::populatefields()
{
	char buffer[256];

	GetWindowText(m_hwnd, buffer, 256);
	m_title = std::string(buffer);

	RECT badtype;
	if (GetWindowRect(this->m_hwnd, &badtype)) {
		m_windowposition.width = badtype.right - badtype.left;
		m_windowposition.height = badtype.bottom - badtype.top;
		m_windowposition.x = badtype.left;
		m_windowposition.y = badtype.top;
	}
}

std::shared_ptr<window> window::make(HWND hwnd)
{
	std::shared_ptr<window> windowptr = std::make_shared<window>(hwnd);
	windowptr->populatefields();
	return windowptr;
}

void window::set_position(int mode, int x, int y, display* display)
{
    auto [dispwidth, dispheight] = display->get_resolution()->as_tuple();
    if (mode == CENTERED) {
        m_windowposition = vec4i(
                abs ( ( dispwidth / 2 ) - x / 2 ),
                abs ( ( dispheight  ) - y  ) / 2,
                x, y);
    }

    refresh_position();
}

void window::unwindowsify()
{
    LONG style = GetWindowLong(m_hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU );
    SetWindowLong(m_hwnd, GWL_STYLE, style);
    // Need to force a repaint
    refresh_position();
}

void window::refresh_position()
{
	MoveWindow(m_hwnd,
		m_windowposition.x,
		m_windowposition.y,
		m_windowposition.width,
		m_windowposition.height,
		TRUE);
}
