#include <easyqt/logging.hxx>
#include <easyqt/utils.hxx>

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
	
	std::string Media::suffixForExtension(std::string ext) {
		ext = std::tolower(ext);
		for (const auto& suffix: _suffixes) {
			if (std::tolower(suffix) == ext) {
				return suffix;
			}
		}
		return "";
	}
	
	std::string Media::suffix(std::string preferred) {
		std::string s;
		if (!preferred.empty()) {
			s = suffixForExtension(preferred);
		}
		if (s.empty()) {
			s = *_suffixes.begin();
		}
		return s;
	}
	
	std::filesystem::path Media::path() {
		return directory() / filename();
	}
}

