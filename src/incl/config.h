#pragma once

#include "windowconfig.h"
#include "hotkeyconfig.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <tuple>

class config {
private:
    std::unordered_map<int, std::string> m_hotkeyconfigs;
    std::vector<windowconfig> m_windowconfigs;
    std::tuple<int, int, int> m_resizeconfig;

public:
    config();
    static std::shared_ptr<config> make();

    void parse();

    std::tuple<int, int, int> & get_resizeconfig() { return m_resizeconfig;  }

    std::vector<windowconfig> &get_windowconfigs() { return m_windowconfigs; }

    std::unordered_map<int, std::string> &get_hotkeyconfigs() { return m_hotkeyconfigs; }
};