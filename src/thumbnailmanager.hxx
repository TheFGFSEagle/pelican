#ifndef PELICAN_THUMBNAILMANAGER_HXX
#define PELICAN_THUMBNAILMANAGER_HXX

#include <filesystem>
#include <string>

#include <QPixmap>

#include "singleton.hxx"

#include "media.hxx"

namespace pelican {
	class ThumbnailManager: public Singleton<ThumbnailManager> {
		public:
			ThumbnailManager();
		
			QPixmap thumbnail(Media* media, int width, int height);
			QPixmap thumbnail(MediaPtr media, int width, int height) { return thumbnail(media.get(), width, height); };
		
		private:
			void generateThumbnail(Media* media, std::filesystem::path path, int width, int height);
			
			std::filesystem::path _thumbnailDirectory;
	};
}

#endif

