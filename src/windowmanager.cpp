#include "windowmanager.h"
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <functional>


static BOOL CALLBACK enumeration_callback(HWND hwnd, LPARAM lparam)
{
	char aids[256];

	unsigned long pid;
	GetWindowThreadProcessId(hwnd, &pid);
	std::cout << pid << "\n";
	HWND owner = GetWindow(hwnd, GW_OWNER);

	if (IsWindowVisible(owner)) {

		GetWindowText(owner, aids, 256);
		auto gay = std::string(aids);
		std::cout << gay << "\n";

		std::shared_ptr<window> windowptr = window::make(hwnd);
		WindowManager* wm = (WindowManager*)lparam;
	}
	return TRUE;
}

void WindowManager::store_windows()
{
	HWND topwin = GetTopWindow(GetDesktopWindow());
	while (topwin = GetWindow(topwin, GW_HWNDNEXT)) {
		if (!IsWindowVisible(topwin))
			continue;

		char buf[256];
		GetWindowText(topwin, buf, 256);
		std::string title = std::string(buf);

		if (title.length() > 1) {
			std::shared_ptr<window> windowptr = window::make(topwin);
			m_windows.push_back(windowptr);
			std::cout << buf << "\n";
		}
	}

}

std::vector<std::shared_ptr<window>>* WindowManager::get_windows()
{
	// This anals cpu
	m_windows.clear();
	store_windows();
	return &m_windows;
}