#ifndef PELICAN_MEDIAINFOPANE_HXX
#define PELICAN_MEDIAINFOPANE_HXX

#include <QGridLayout>
#include <QLabel>
#include <QWidget>

#include "singleton.hxx"

#include "media.hxx"

namespace pelican {
	class MediaInfoPane: public Singleton<MediaInfoPane, QWidget> {
		Q_OBJECT
		public:
			MediaInfoPane();
			void setMedia(MediaPtr media);
			void showMediaInfo();
		
		private:
			QGridLayout _layout;
			QLabel _nameLabel, _focalLengthLabel, _shutterSpeedLabel, _apertureLabel, _isoLabel;
			MediaPtr _media;
	};
}

#endif

