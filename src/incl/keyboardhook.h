#pragma once
#include <Windows.h>
#include  <vector>

static HHOOK keebhook;
static std::vector<LPKBDLLHOOKSTRUCT> inputs{};

static LRESULT CALLBACK kbproc(int code, WPARAM wparam, LPARAM lparam)
{
    if ((wparam == WM_KEYDOWN) && lparam != NULL) {
        auto input = (LPKBDLLHOOKSTRUCT)lparam;
        if (input->vkCode == 0x34) {

            if (!(GetAsyncKeyState(VK_RCONTROL) & 1))   goto END;

            inputs.push_back(input);
            return 1;
        }
    }

END:
    return CallNextHookEx(NULL, code, wparam, lparam);
}

void hook_keyboard()
{
    keebhook = SetWindowsHookExW(WH_KEYBOARD_LL, kbproc, NULL, 0);
//    MSG msg;
//    while (!GetMessage(&msg, NULL, 0, 0)) {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//    UnhookWindowsHookEx(keebhook);
}

void unhook_keyboard()
{
    UnhookWindowsHookEx(keebhook);
}