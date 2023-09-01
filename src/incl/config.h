#pragma once
#include "windowconfig.h"
#include "hotkeyconfig.h"
#include <memory>
#include <vector>

class config {
private:
    std::vector<windowconfig> m_windowconfigs;
    std::vector<hotkeyconfig> m_hotkeyconfigs;

public:
    static std::shared_ptr<config> make();
    void parse();
    std::vector<windowconfig>& get_windowconfigs() { return m_windowconfigs; };
    std::vector<hotkeyconfig>& get_hotkeyconfigs() { return m_hotkeyconfigs; };
};