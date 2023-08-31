#include <iostream>
#include "window.h"
#include "windowmanager.h"

int main()
{
	int width = 2560;
	int height = 1400;
	int x = (5120 / 2) - (width / 2);
	int y = (1440 / 2) - (height / 2);

	// TODO: Testing remove me
	WindowManager* wm = new WindowManager();
	for (auto& window : *wm->get_windows()) {
		if (window->get_title()->contains("RuneScape")) {
			auto pos = window->get_position();
			window->get_position()->print();
			pos->x = x;
			pos->y = y;
			pos->width = width;
			pos->height = height;
			window->refresh_position();
			SetForegroundWindow(window->get_hwnd());
			window->get_position()->print();
		}
	}
}
