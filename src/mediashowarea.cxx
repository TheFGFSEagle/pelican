#include <QPixmap>
#include <QThreadPool>

#include <easyqt/logging.hxx>

#include "mediashowarea.hxx"

namespace pelican {
	MediaShowArea::MediaShowArea(): _mediaLabel(this) {
	}
	
	void MediaShowArea::setMedia(MediaPtr media) {
		_media = media;
		QThreadPool::globalInstance()->start(std::bind(&MediaShowArea::showMedia, this));
	}
	
	void MediaShowArea::showMedia() {
		_image = QPixmap(_media->path().concat(_media->suffix(".jpg")).c_str());
		_mediaLabel.setPixmap(_image.scaled(size(), Qt::KeepAspectRatio));
	}
	
	void MediaShowArea::resizeEvent(QResizeEvent* event) {
		_mediaLabel.setPixmap(_image.scaled(event->size(), Qt::KeepAspectRatio));
		_mediaLabel.resize(size());
	}
}

