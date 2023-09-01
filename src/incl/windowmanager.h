#include "window.h"
#include <vector>
#include <memory>
#include "config.h"
#include "display.h"

class WindowManager {
private:
	std::vector<std::shared_ptr<window>> m_windows;

public:
	std::vector<std::shared_ptr<window>>& get_windows();
	void store_windows();
    void apply_config_targeted(std::string, std::shared_ptr<config>, display*);
    void minimize_all_but(std::string);
};