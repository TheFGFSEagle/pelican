#include <QDir>
#include <QImage>
#include <QImageReader>
#include <QLabel>
#include <QPixmap>
#include <QVariant>

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
		QLabel* thumbnailLabel = new QLabel;
		thumbnailLabel->setPixmap(media->thumbnail(THUMBNAIL_SIZE, THUMBNAIL_SIZE));
		_layout.addWidget(thumbnailLabel, 0, 0);
		_layout.setAlignment(thumbnailLabel, Qt::AlignCenter);
		QLabel* nameLabel = new QLabel(media->filename().c_str());
		_layout.addWidget(nameLabel, 1, 0);
		_layout.setAlignment(nameLabel, Qt::AlignCenter);
	}
	
	MediaView::MediaView() {
		setLayout(&_layout);
	}
	
	void MediaView::rebuild() {
		QLayoutItem* item;
		while ((item = _layout.takeAt(9))) {
			delete item->widget();
		}

		int i = 0;
		for (const auto& media: Application::instance()->medias()) {
			if (i > 10) {
				break;
			}
			_layout.addWidget(new MediaViewEntry(media));
			i++;
		}
	}
}

