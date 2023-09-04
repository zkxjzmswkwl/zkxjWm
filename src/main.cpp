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
    auto windowconfigs = config->get_windowconfigs();
    printf("%d/%d\n", resize_stepamount, resize_keycode);

    int idx = 0;
    for (auto& wconfig : windowconfigs) {
        RegisterHotKey(0, idx++, MOD_ALT | MOD_NOREPEAT, wconfig.first);
    }

    // Registers hotkeys to resize the currently focused window.
    //      int stepamount : amount of pixels to resize by in one press
    //      int keycode    : non-modifier keycode to trigger the resize
    // LSHIFT is set as an additional modifier to shrink the window using same key as grow.
    RegisterHotKey(0, idx++, MOD_ALT | MOD_NOREPEAT, resize_keycode);
    RegisterHotKey(0, idx++, MOD_ALT | MOD_SHIFT | MOD_NOREPEAT, resize_keycode);

    auto configcount = windowconfigs.size();
    MSG msg = {0};
    while (GetMessage(&msg, 0, 0, 0) != 0) {
        if (msg.message != WM_HOTKEY) continue;

        if (msg.wParam >= configcount) {
            // temp hack: This is a waste currently. `window` is destroyed immediately.
            auto currentwindow = window::make(GetForegroundWindow());
            auto modifier_loword = LOWORD(msg.lParam);
            // If only ALT was passed as a modifier.
            if (modifier_loword == 1) {
                currentwindow->resize_evenly(resize_stepamount);
                continue;
            }
            // If it was any other combinations of modifiers.
            currentwindow->resize_evenly(resize_stepamount * -1);
        } else {
            SHORT keycode = HIWORD(msg.lParam);
            wm->apply_config_targeted(windowconfigs.at(keycode).substr, config, currentdisplay);
        }
    }
}