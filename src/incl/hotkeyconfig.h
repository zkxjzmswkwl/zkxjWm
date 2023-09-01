#pragma once
#include <string>

struct hotkeyconfig {
    hotkeyconfig(std::string target, int keycode) : target(target), keycode(keycode) {}
    std::string target;
    int keycode;
};