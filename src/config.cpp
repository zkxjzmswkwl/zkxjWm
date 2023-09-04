#include "config.h"
#include <toml.hpp>

config::config()
{
    this->parse();
}

std::shared_ptr<config> config::make()
{
    return std::make_shared<config>();
}

void config::parse()
{
    auto data = toml::parse("test.toml");
    const auto windowtables = toml::find<toml::array>(data, "window");
    const auto hotkeytables = toml::find<toml::array>(data, "hotkey");
    const auto& growtable = toml::find(data, "grow");

    for (auto table : windowtables) {
        auto substr = toml::find<std::string>(table, "substr");
        auto size = toml::find<std::vector<int>>(table, "size");
        auto centered = toml::find<bool>(table, "center");
        auto borderless = toml::find<bool>(table, "borderless");
        auto minimizeAll = toml::find<bool>(table, "minimizeAll");

        printf("%d/%d\n", size.at(0), size.at(1));

        windowconfig wc(substr, size, centered, borderless, minimizeAll);
        m_windowconfigs.push_back(wc);
    }

    for (auto table : hotkeytables) {
        auto target = toml::find<std::string>(table, "target");
        auto keycode = toml::find<int>(table, "keycode");
        m_hotkeyconfigs[keycode] = target;
    }

    std::get<0>(m_resizeconfig) = toml::find<int>(growtable, "stepamount");
    std::get<1>(m_resizeconfig) = toml::find<int>(growtable, "keycode");
    std::get<2>(m_resizeconfig) = toml::find<int>(growtable, "shrink");
}
