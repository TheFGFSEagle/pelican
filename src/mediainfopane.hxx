#ifndef PELICAN_MEDIAINFOPANE_HXX
#define PELICAN_MEDIAINFOPANE_HXX

#include <QWidget>
#include <QGridLayout>

#include "singleton.hxx"

namespace pelican {
	class MediaInfoPane: public Singleton<MediaInfoPane, QWidget> {
		private:
			QGridLayout* _layout;
	};
}

#endif

