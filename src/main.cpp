#include "windowmanager.h"
#include "display.h"
#include "config.h"

int main()
{
    auto config = config::make();
    auto currentdisplay = display::make();
    // Rename WindowManager to windowmanager or some other shit that's at least consistent
	auto wm = WindowManager::make();

    auto [resize_stepamount, resize_keycode, resize_shrink] = config->get_resizeconfig();
    auto hotkeyconfigs = config->get_hotkeyconfigs();
    printf("%d/%d/%d\n", resize_stepamount, resize_keycode, resize_shrink);

    // This is kinda fucking dumb
    int idx = 1;
    for (auto& hotkey : hotkeyconfigs) {
        RegisterHotKey(0, idx, MOD_ALT | MOD_NOREPEAT, hotkey.first);
        idx++;
    }

    // temp hack: Register [grow] hotkey
    RegisterHotKey(0, idx++, MOD_ALT | MOD_NOREPEAT, resize_keycode);
    RegisterHotKey(0, idx++, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, resize_keycode);

    MSG msg = {0};
    while (GetMessage(&msg, 0, 0, 0) != 0) {
        if (msg.message != WM_HOTKEY) {
            continue;
        }

        if (msg.wParam == 3 || msg.wParam == 4) {
            // temp hack: This is a waste currently. `window` is destroyed immediately.
            auto currentwindow = window::make(GetForegroundWindow());
            auto modifier_loword = LOWORD(msg.lParam);
            // If the modifier key used was just ALT
            if (modifier_loword != 1) {
                currentwindow->resize_evenly(resize_stepamount);
                continue;
            }
            // If it was any other combinations of modifiers.
            currentwindow->resize_evenly(resize_stepamount * -1);
        } else {
            SHORT keycode = HIWORD(msg.lParam);
            wm->apply_config_targeted(hotkeyconfigs.at(keycode), config, currentdisplay);
        }
    }
}