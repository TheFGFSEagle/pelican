#include "media.hxx"
#include "thumbnailmanager.hxx"

namespace pelican {
	void Media::addSuffix(std::filesystem::path suffix) {
		_suffixes.insert(suffix.string());
	}
	
	void Media::addSuffix(std::string suffix) {
		_suffixes.insert(suffix);
	}
	
	QPixmap Media::thumbnail(int width, int height) {
		return ThumbnailManager::instance()->thumbnail(this, width, height);
	}
}

