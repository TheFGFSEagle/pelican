#ifndef PELICAN_MEDIA_HXX
#define PELICAN_MEDIA_HXX

#include <filesystem>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <QPixmap>

namespace pelican {
	class Media {
		public:
			Media(std::filesystem::path directory, std::string filename, std::set<std::string> suffixes = {}):
					_directory(directory), _filename(filename), _suffixes(suffixes)
			{};
		
			void addSuffix(std::filesystem::path suffix);
			void addSuffix(std::string suffix);
			
			QPixmap thumbnail(int width, int height);
			
			std::filesystem::path directory() { return _directory; };
			std::string filename() { return _filename; };
			std::set<std::string> suffixes() { return _suffixes; };
		
		private:
			std::filesystem::path _directory;
			std::string _filename;
			std::set<std::string> _suffixes;
	};
	
	using MediaPtr = std::shared_ptr<Media>;
	using MediaPtrVector = std::vector<MediaPtr>;
}

#endif

