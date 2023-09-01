#pragma once
#include <iostream>
#include <tuple>

struct vec4i {
    vec4i(int x, int y, int width, int height) : x{x}, y{y}, width{width}, height{height} {}
    vec4i() {}
    int x;
    int y;
    int width;
    int height;

    void print() {
        printf("%d, %d, %d, %d\n", x, y, width, height);
    }
};

struct vec2i {
    vec2i(int width, int height) : width(width), height(height) {}
    vec2i() {}
    int width;
    int height;

    std::tuple<int, int> as_tuple()
    {
        return std::tuple<int, int> {
            width, height
        };
    }
};