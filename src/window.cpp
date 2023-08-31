#include "window.h"
#include <iostream>

template class std::shared_ptr<window>;

window::window()
{
    m_windowposition = vec4i{ 1, 1, 1, 1 } ;
    m_keycombo = keycombo(0xA3, 'K');
}

window::window(HWND hwnd)
{
	printf("called window ctor w hwnd\n");
    this->m_hwnd = hwnd;
}

void window::populatefields()
{
	char aids[256];

	GetWindowText(m_hwnd, aids, 256);
	m_title = std::string(aids);

	std::cout << m_title << "\n";

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

void window::refresh_position()
{
	MoveWindow(m_hwnd,
		m_windowposition.x,
		m_windowposition.y,
		m_windowposition.width,
		m_windowposition.height,
		TRUE);
}
