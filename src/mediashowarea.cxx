#include <cmath>

#include <QPixmap>
#include <QThreadPool>

#include <easyqt/logging.hxx>

#include "mediashowarea.hxx"

namespace pelican {
	MediaShowArea::MediaShowArea(): _mediaLabel(this) {
		setMouseTracking(true);
		setFocusPolicy(Qt::ClickFocus);
	}
	
	void MediaShowArea::setMedia(MediaPtr media) {
		_media = media;
		QThreadPool::globalInstance()->start(std::bind(&MediaShowArea::showMedia, this));
	}
	
	void MediaShowArea::showMedia() {
		_image = QPixmap(_media->path().concat(_media->suffix(".jpg")).c_str());
		QSize newSize = _image.size().scaled(size(), Qt::KeepAspectRatio);
		double scale = (double)newSize.width() / _image.size().width();
		setMediaScale(scale);
	}
	
	void MediaShowArea::resizeEvent(QResizeEvent* event) {
		if (_scale == -1) {
			setMediaScale(_scale);
		} else  {
			QSize newSize = _image.size().scaled(event->size(), Qt::KeepAspectRatio);
			double scale = (double)newSize.width() / _image.size().width();
			setMediaScale(scale);
		}
	}
	
	void MediaShowArea::setMediaScale(double scale) {
		_scale = scale;
		LOG(DEBUG, "Setting media display scale to " << _scale * 100 << "%";)
		QSize newSize = _image.size() * scale;
		_mediaLabel.setPixmap(_image.scaled(newSize, Qt::KeepAspectRatio));
		_mediaLabel.resize(newSize);
	}
	
	void MediaShowArea::keyPressEvent(QKeyEvent* event) {
		if (event->key() == Qt::Key_Escape) {
			hide();
		} else {
			MediaView::instance()->keyPressEvent(event);
		}
		
		QWidget::keyPressEvent(event);
	}
	
	void MediaShowArea::mousePressEvent(QMouseEvent* event) {
		if (event->buttons() == Qt::LeftButton) {
			_lastMousePosition = event->pos();
		} else {
			_lastMousePosition = QPoint();
		}
	}
	
	void MediaShowArea::mouseMoveEvent(QMouseEvent* event) {
		if (event->buttons() == Qt::LeftButton) {
			if (!_lastMousePosition.isNull()) {
				QPoint currentMousePosition = event->pos();
				QPoint delta = currentMousePosition - _lastMousePosition;
				_mediaLabel.move(_mediaLabel.pos() + delta);
				_lastMousePosition = currentMousePosition;
			}
		}
	}
	
	void MediaShowArea::mouseReleaseEvent(QMouseEvent* event) {
		_lastMousePosition = QPoint();
	}
}

