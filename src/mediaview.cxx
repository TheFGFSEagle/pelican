#include <QImage>
#include <QPixmap>
#include <QThreadPool>

#include <easyqt/logging.hxx>

#include "application.hxx"
#include "mediaview.hxx"

#define THUMBNAIL_SIZE 128

namespace pelican {
	MediaViewEntry::MediaViewEntry(MediaPtr media):
			_media(media)
	{
		setFixedWidth(THUMBNAIL_SIZE + 10);
		setLayout(&_layout);
		_thumbnailLabel.setFixedSize(THUMBNAIL_SIZE, THUMBNAIL_SIZE);
		_thumbnailLabel.setPixmap(QIcon::fromTheme("image-jpg").pixmap(THUMBNAIL_SIZE, THUMBNAIL_SIZE));
		_layout.addWidget(&_thumbnailLabel, 0, 0);
		_layout.setAlignment(&_thumbnailLabel, Qt::AlignCenter);
		_nameLabel.setText(media->filename().c_str());
		_layout.addWidget(&_nameLabel, 1, 0);
		_layout.setAlignment(&_nameLabel, Qt::AlignCenter);
		
		QThreadPool::globalInstance()->start(std::bind(&MediaViewEntry::showThumbnail, this));
	}
	
	void MediaViewEntry::showThumbnail() {
		_thumbnailLabel.setPixmap(_media->thumbnail(THUMBNAIL_SIZE, THUMBNAIL_SIZE));
	}
	
	MediaView::MediaView() {
		setLayout(&_layout);
	}
	
	void MediaView::rebuild() {
		QLayoutItem* item;
		while ((item = _layout.takeAt(9))) {
			delete item->widget();
		}

		for (const auto& media: Application::instance()->medias()) {
			_layout.addWidget(new MediaViewEntry(media));
		}
	}
}

