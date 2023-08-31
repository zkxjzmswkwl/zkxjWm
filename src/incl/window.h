#pragma once
#include <string>
#include <windows.h>
#include <memory>

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

struct keycombo {
    keycombo(int modifier, int key) : modifier(modifier), key(key) {}
    keycombo() {}
    int modifier;
    int key;
};

class window {
private:
    // Last polled, not always up to date, but should be when accessed.
    vec4i m_windowposition;
    keycombo m_keycombo;
    HWND m_hwnd;
    HANDLE m_prochandle;
    std::string m_title;
    bool m_visible;

public:
    window();
    window(HWND);

    void populatefields();
    void refresh_position();

    HWND get_hwnd() { return m_hwnd; }
    std::string * get_title() { return &m_title;  }
    vec4i * get_position() { return &m_windowposition;  }

    static std::shared_ptr<window> make(HWND);
};