#include "keyboardhook.h"
#include "windowmanager.h"
#include "display.h"
#include "config.h"

int main()
{
    auto config = config::make();
    auto currentdisplay = display::make();
    // Rename WindowManager to windowmanager or some other shit that's at least consistent
	auto wm = WindowManager::make();

    auto hotkeyconfigs = config->get_hotkeyconfigs();

    // This is kinda fucking dumb
    int idx = 1;
    for (auto& hotkey : hotkeyconfigs) {
        RegisterHotKey(0, idx, MOD_ALT | MOD_NOREPEAT, hotkey.keycode);
        idx++;
    }

    RegisterHotKey(0, idx++, MOD_ALT | MOD_NOREPEAT, 0x32);
    printf("%d hotkeys loaded.\n", idx - 1);

    MSG msg = {0};
    while (GetMessage(&msg, 0, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {

            // Region Test code remove me
            if (msg.wParam - 1 == 0x32) {

            }
            // End Region
            auto hkc = hotkeyconfigs.at(msg.wParam - 1);
            wm->apply_config_targeted(hkc.target, config, currentdisplay);

        }
    }
}