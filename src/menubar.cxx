#include "menubar.hxx"

namespace pelican {
	void MenuBar::init(std::string name) {
		LOG(DEBUG, "Initializing pelican::MenuBar with name " << name);
		std::string file;
		if (name == "pelican::GlobalMenuBar") {
			file = "res:ui/menubar.xml";
		}
		if (!file.empty()) {
			loadFromFile(file);
		}
	}
}

