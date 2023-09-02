#pragma once

#include "vec.h"
#include "windowconfig.h"
#include "display.h"
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

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
    HWND m_hwnd;
    std::string m_title;
    bool m_visible;
    windowconfig config;

public:
    enum {
        CENTERED, ABS, FIT, FIT_GAPS
    };

    window();

    window(HWND);

    void populatefields();

    void refresh_position();

    HWND get_hwnd() { return m_hwnd; }

    std::string get_title() { return m_title; }

    vec4i *get_position() { return &m_windowposition; }

    windowconfig *get_config() { return &config; }

    static std::shared_ptr<window> make(HWND);

    void set_position(int mode, int x, int y, int displaywidth, int displayheight);

    void unwindowsify();
};