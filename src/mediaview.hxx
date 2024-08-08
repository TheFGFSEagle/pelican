#ifndef PELICAN_MEDIALIST_HXX
#define PELICAN_MEDIALIST_HXX

#include <QFileSystemWatcher>
#include <QGridLayout>
#include <QLabel>
#include <QWidget>

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
			void showThumbnail();
		
		private:
			QGridLayout _layout;
			QLabel _thumbnailLabel;
			QLabel _nameLabel;
			
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

