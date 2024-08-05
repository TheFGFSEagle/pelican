#include "thumbnailmanager.hxx"

namespace pelican {
	QPixmap ThumbnailManager::thumbnail(Media* media, int width, int height) {
		std::filesystem::path path = (media->directory() / media->filename()).concat(".JPG");
		QPixmap preview = QPixmap(path.c_str());
		return preview.scaled(width, height, Qt::KeepAspectRatio);
	}
}

