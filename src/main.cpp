#include "keyboardhook.h"
#include "windowmanager.h"
#include "display.h"
#include "config.h"

int main()
{
    auto config = config::make();
    auto currentdisplay = new display();
	auto wm = new WindowManager();
    auto hotkeyconfigs = config->get_hotkeyconfigs();
    currentdisplay->refresh_resolution();

    int idx = 1;
    for (auto& hotkey : hotkeyconfigs) {
        RegisterHotKey(NULL, idx, MOD_ALT | MOD_NOREPEAT, hotkey.keycode);
        idx++;
    }
    printf("%d hotkeys loaded.\n", idx);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            auto hkc = hotkeyconfigs.at(msg.wParam - 1);
            wm->apply_config_targeted(hkc.target, config, currentdisplay);
        }
    }
}
