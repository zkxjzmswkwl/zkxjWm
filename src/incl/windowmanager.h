#include "window.h"
#include <vector>
#include <memory>

class WindowManager {
private:
	std::vector<std::shared_ptr<window>> m_windows;

public:
	std::vector<std::shared_ptr<window>>* get_windows();
	void store_windows();
};