#include "windowmanager.h"
#include <string>
#include <iostream>
#include <functional>

static BOOL CALLBACK enumeration_callback(HWND hwnd, LPARAM lparam)
{
	HWND owner = GetWindow(hwnd, GW_OWNER);

	if (IsWindowVisible(owner)) {
		std::shared_ptr<window> windowptr = window::make(hwnd);
	}
	return TRUE;
}

void WindowManager::store_windows()
{
	HWND topwin = GetTopWindow(GetDesktopWindow());

	while ((topwin = GetWindow(topwin, GW_HWNDNEXT))) {
		if (!IsWindowVisible(topwin))
			continue;

        // Creating a string just to call length() is dumb as fuck given that we do the same operation later to store it.
		char buf[256];
		GetWindowText(topwin, buf, 256);
		std::string title = std::string(buf);

		if (title.length() > 3) {
			std::shared_ptr<window> windowptr = window::make(topwin);
			m_windows.push_back(windowptr);
		}
	}
}

std::vector<std::shared_ptr<window>> & WindowManager::get_windows()
{
	// This anals cpu
	m_windows.clear();
	store_windows();
	return m_windows;
}

void WindowManager::apply_config_targeted(std::string substr, std::shared_ptr<config> config, std::shared_ptr<display> display)
{
    for (auto& window : get_windows()) {
        if (!window->get_title().contains(substr))  continue;

        // Region - This is fucked
        windowconfig wc;
        for (auto& wconfig : config->get_windowconfigs()) {
            if (wconfig.substr == substr) {
                wc = wconfig;
                break;
            }
        }
        // End Region

        ShowWindow(window->get_hwnd(), SW_RESTORE);
        SetForegroundWindow(window->get_hwnd());

        if (wc.center) {
            auto [displaywidth, displayheight] = display->get_resolution().as_tuple();
            window->set_position(
                    window::CENTERED,
                    wc.size.at(0),
                    wc.size.at(1),
                    displaywidth,
                    displayheight);
        } else {
            // TODO: Filler values 0,0 - not actually used unless window::CENTERED passed as mode.
            // Fix them being required.
            window->set_position(window::ABS, wc.size.at(0), wc.size.at(1), 0, 0);
        }

        if (wc.minimizeAll) {
            minimize_all_but(window->get_title());
        }

        if (wc.borderless) {
            window->unwindowsify();
        }
    }
}

void WindowManager::minimize_all_but(std::string target) {
    auto openwindows = get_windows();
    for (auto& window : openwindows) {
        if (window->get_title().contains(target)) continue;
        ShowWindow(window->get_hwnd(), SW_MINIMIZE);
    }
}

std::shared_ptr<WindowManager> WindowManager::make()
{
    return std::make_shared<WindowManager>();
}


