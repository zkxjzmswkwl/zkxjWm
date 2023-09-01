#pragma once
#include <string>
#include <vector>

struct windowconfig {
    windowconfig(
            std::string substr, std::vector<int> size, bool center, bool borderless, bool minimizeAll) :
            substr(substr), size(size), center(center), borderless(borderless), minimizeAll(minimizeAll) {}

    windowconfig() {}

    std::string substr;
    std::vector<int> size;
    bool center;
    bool borderless;
    bool minimizeAll;
};
