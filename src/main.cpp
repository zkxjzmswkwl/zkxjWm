#include "windowmanager.h"
#include "display.h"
#include "config.h"

int main()
{
    auto config = config::make();
    auto currentdisplay = display::make();
    // Rename WindowManager to windowmanager or some other shit that's at least consistent
	auto wm = WindowManager::make();

    auto [resize_stepamount, resize_keycode] = config->get_resizeconfig();
    auto hotkeyconfigs = config->get_hotkeyconfigs();

    // This is kinda fucking dumb
    int idx = 1;
    for (auto& hotkey : hotkeyconfigs) {
        RegisterHotKey(0, idx, MOD_ALT | MOD_NOREPEAT, hotkey.keycode);
        idx++;
    }

    // temp hack: Register [grow] hotkey
    RegisterHotKey(0, idx++, MOD_ALT | MOD_NOREPEAT, resize_keycode);

    MSG msg = {0};
    while (GetMessage(&msg, 0, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            if (msg.wParam == 3) {
                // temp hack: This is a waste currently. `window` is destroyed immediately.
                auto currentwindow = window::make(GetForegroundWindow());
                currentwindow->resize_evenly(resize_stepamount);
            } else {
                auto hkc = hotkeyconfigs.at(msg.wParam - 1);
                wm->apply_config_targeted(hkc.target, config, currentdisplay);
            }
        }
    }
}