#pragma once

#include "windowconfig.h"
#include <unordered_map>
#include <memory>
#include <vector>
#include <tuple>

class config {
private:
    std::unordered_map<int, windowconfig> m_windowconfigs;
    std::tuple<int, int> m_resizeconfig;

public:
    config();
    static std::shared_ptr<config> make();

    void parse();

    std::tuple<int, int> & get_resizeconfig() { return m_resizeconfig;  }

    std::unordered_map<int, windowconfig> &get_windowconfigs() { return m_windowconfigs; }

};