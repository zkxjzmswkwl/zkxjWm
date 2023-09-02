#pragma once

#include "vec.h"
#include <memory>

class display {
private:
    vec2i m_resolution;
public:
    display();

    void refresh_resolution();

    vec2i & get_resolution();

    static std::shared_ptr<display> make();
};