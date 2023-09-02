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

protected:
    void store_current_title();

    void store_current_position();

    void apply_position();

public:
    enum {
        CENTERED, ABS, FIT, FIT_GAPS
    };

    window(HWND);

    HWND get_hwnd() { return m_hwnd; }

    std::string get_title() { return m_title; }

    vec4i *get_position() { return &m_windowposition; }

    windowconfig *get_config() { return &config; }

    void set_position(int mode, int x, int y, int displaywidth, int displayheight);

    void unwindowsify();

    void resize_evenly(int amount);

    static std::shared_ptr<window> make(HWND);
};