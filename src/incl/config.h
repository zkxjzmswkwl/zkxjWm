#pragma once

#include "windowconfig.h"
#include "hotkeyconfig.h"
#include <memory>
#include <vector>
#include <tuple>

class config {
private:
    std::vector<windowconfig> m_windowconfigs;
    std::vector<hotkeyconfig> m_hotkeyconfigs;
    std::tuple<int, int>      m_resizeconfig;

public:
    static std::shared_ptr<config> make();

    void parse();

    std::tuple<int, int> & get_resizeconfig()      { return m_resizeconfig;  }

    std::vector<windowconfig> &get_windowconfigs() { return m_windowconfigs; }

    std::vector<hotkeyconfig> &get_hotkeyconfigs() { return m_hotkeyconfigs; }
};