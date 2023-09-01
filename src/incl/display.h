#pragma once
#include "vec.h"

class display {
private:
    vec2i m_resolution;
public:
    display() = default;

    void refresh_resolution();
    vec2i * get_resolution();
};