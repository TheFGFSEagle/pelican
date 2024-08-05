#ifndef PELICAN_MEDIALIST_HXX
#define PELICAN_MEDIALIST_HXX

#include <QWidget>
#include <QFileSystemWatcher>

#include <filesystem>
#include <set>

#include <easyqt/flowlayout.hxx>

#include "singleton.hxx"

#include "media.hxx"

namespace pelican {
	class MediaViewEntry: public QWidget {
		Q_OBJECT
		
		public:
			MediaViewEntry(MediaPtr media);
		
		private:
			QGridLayout _layout;
			MediaPtr _media;
	};
	
	class MediaView: public Singleton<MediaView, QWidget> {
		Q_OBJECT
		
		public:
			MediaView();
			void rebuild();
		
		private:
			easyqt::FlowLayout _layout;
	};
} 

#endif

