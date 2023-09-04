#pragma once

#include <string>
#include <vector>

struct windowconfig {
    // this is ugly. someone should probably do something about that.
    windowconfig(
            std::string substr, std::vector<int> size, bool center, bool borderless, bool minimizeAl) :
            substr(substr), size(size), center(center), borderless(borderless), minimizeAll(minimizeAll)
            {}

    windowconfig() {}

    std::string substr;
    std::vector<int> size;
    bool center;
    bool borderless;
    bool minimizeAll;
};
