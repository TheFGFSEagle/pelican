#include <ranges>

#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QRubberBand>
#include <QSize>
#include <QThreadPool>

#include <easyqt/logging.hxx>

#include "application.hxx"
#include "mediaview.hxx"

#define THUMBNAIL_SIZE 128
#define HOVER_COLOR "#bcf"
#define SELECTED_COLOR "#8af"

namespace pelican {
	MediaViewEntry::MediaViewEntry(MediaPtr media):
			_media(media)
	{
		setLayout(&_layout);
		setFixedWidth(THUMBNAIL_SIZE + 20);
		setFocusPolicy(Qt::NoFocus);
		
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
	
	void MediaViewEntry::paintEvent(QPaintEvent *event) {
		QPainter painter;
		painter.begin(this);
		
		if (_selected) {
			painter.fillRect(rect(), QColor(SELECTED_COLOR));
		} else if (underMouse()) {
			painter.fillRect(rect(), QColor(HOVER_COLOR));
		}
		painter.end(); 
		
		QWidget::paintEvent(event);
	}
	
	void MediaViewEntry::mousePressEvent(QMouseEvent* event) {
		if (event->button() == Qt::LeftButton) {
			MediaView::SelectionOperation op = MediaView::ReplaceSelection;
			if (event->modifiers() & Qt::ShiftModifier) {
				op = MediaView::AddRangeToSelection;
			} else if (event->modifiers() & Qt::ControlModifier) {
				if (_selected) {
					op = MediaView::RemoveFromSelection;
				} else {
					op = MediaView::AddToSelection;
				}
			}
			if (!_selected) {
				MediaView::instance()->selectEntry(this, op);
			}
		}
	}
	
	void MediaViewEntry::mouseReleaseEvent(QMouseEvent* event) {}
	
	void MediaViewEntry::enterEvent(QEvent* event) {
		update();
	}
	
	void MediaViewEntry::leaveEvent(QEvent* event) {
		update();
	}
	
	void MediaViewEntry::setSelected(bool selected) {
		_selected = selected;
		update();
	}
	
	MediaView::MediaView():
			_rubberBand(QRubberBand::Rectangle, this)
	{
	
		setLayout(&_layout);
		setFocusPolicy(Qt::ClickFocus);
	}
	
	void MediaView::rebuild() {
		while (_layout.takeAt(0)) {
		}
		for (MediaViewEntry* entry: _mediaEntries) {
			delete entry;
		}
		_mediaEntries.clear();
		
		for (const auto& media: Application::instance()->medias()) {
			MediaViewEntry* mediaEntry = new MediaViewEntry(media);
			_mediaEntries.push_back(mediaEntry); 
			_layout.addWidget(mediaEntry);
		}
	}
	
	void MediaView::selectEntry(MediaViewEntry* entry, SelectionOperation op) {
		if (op == ReplaceSelection) {
			clearSelection();
			entry->setSelected(true);
			_selectionStartEntry = entry;
		} else if (op == AddToSelection) {
			entry->setSelected(true);
			_selectionStartEntry = entry;
		} else if (op == RemoveFromSelection) {
			entry->setSelected(false);
			_selectionStartEntry = nullptr;
		} else if (op == AddRangeToSelection) {
			if (!_selectionStartEntry) {
				selectEntry(entry, ReplaceSelection);
				return;
			}
			
			auto entryIt = std::find(_mediaEntries.begin(), _mediaEntries.end(), entry);
			auto selectionStartEntryIt = std::find(_mediaEntries.begin(), _mediaEntries.end(), _selectionStartEntry);
			clearSelection();
			if (selectionStartEntryIt != entryIt) {
				if (selectionStartEntryIt > entryIt) {
					std::swap(selectionStartEntryIt, entryIt);
				}
  				for (; selectionStartEntryIt != entryIt; selectionStartEntryIt++) {
					(*selectionStartEntryIt)->setSelected(true);
				}
			}
			_selectionStartEntry->setSelected(true);
			entry->setSelected(true);
		}
	}
	
	void MediaView::selectAll() {
		for (const auto& mediaEntry: _mediaEntries) {
			mediaEntry->setSelected(true);
		}
		_selectionStartEntry = nullptr;
	}
	
	void MediaView::invertSelection() {
		for (const auto& mediaEntry: _mediaEntries) {
			mediaEntry->setSelected(!mediaEntry->selected());
		}
	}
	
	void MediaView::clearSelection() {
		for (const auto& mediaEntry: _mediaEntries) {
			mediaEntry->setSelected(false);
		}
	}
	
	void MediaView::mousePressEvent(QMouseEvent* event) {
		clearSelection();
		
		_rubberBandOrigin = event->pos();
		_rubberBand.setGeometry(QRect(_rubberBandOrigin, QSize()));
		_rubberBand.show();
		QWidget::mousePressEvent(event);
	}

	void MediaView::mouseMoveEvent(QMouseEvent* event) {
		_rubberBand.setGeometry(QRect(_rubberBandOrigin, event->pos()).normalized());
		
		QWidget* widget;
		bool selected = false;
		for (auto it = _mediaEntries.begin(); it != _mediaEntries.end(); it++) {
			selected = (*it)->geometry().intersects(_rubberBand.geometry());
			(*it)->setSelected(selected);
		}
		
		QWidget::mouseMoveEvent(event);
	}

	void MediaView::mouseReleaseEvent(QMouseEvent* event) {
		_rubberBand.hide();
		QWidget::mouseReleaseEvent(event);
	}
	
	void MediaView::keyPressEvent(QKeyEvent* event) {
		if (event->key() == Qt::Key_Left) {
			auto it = std::ranges::find(_mediaEntries, _selectionStartEntry);
			if (it != _mediaEntries.end() and it != _mediaEntries.begin()) {
				if (event->modifiers() == Qt::NoModifier) {
					selectEntry(*(--it), ReplaceSelection);
				} else if (event->modifiers() & Qt::ShiftModifier) {
					selectEntry(*(--it), AddToSelection);
				}
			}
		} else if (event->key() == Qt::Key_Right) {
			auto it = std::ranges::find(_mediaEntries, _selectionStartEntry);
			if (it != _mediaEntries.end()) {
				if (event->modifiers() == Qt::NoModifier) {
					selectEntry(*(++it), ReplaceSelection);
				} else if (event->modifiers() & Qt::ShiftModifier) {
					selectEntry(*(++it), AddToSelection);
				}
			}
		} else if (event->modifiers() & Qt::ControlModifier) {
			if (event->key() == Qt::Key_A) {
				selectAll();
			} else if (event->key() == Qt::Key_I) {
				invertSelection();
			}
		} else if (event->key() == Qt::Key_Delete) {
		}

		QWidget::keyPressEvent(event);
	}
}

