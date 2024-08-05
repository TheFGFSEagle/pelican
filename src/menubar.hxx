#ifndef PELICAN_MENUBAR_HXX
#define PELICAN_MENUBAR_HXX

#include <easyqt/logging.hxx>
#include <easyqt/menubar.hxx>

namespace pelican {
	class MenuBar: public Singleton<MenuBar, easyqt::MenuBar> {
		Q_OBJECT
		public:
			MenuBar(std::string name = "") {
			}
			virtual void init(std::string name = "");
	};
}

#endif

