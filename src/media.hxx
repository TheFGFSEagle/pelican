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
		
			// @description Add suffix (file type) for this media 
			//	(photos often come in JPG and RAW formats, videos might have a thumbnail)
			// @param suffix Suffix to add
			void addSuffix(std::filesystem::path suffix);
			void addSuffix(std::string suffix);
			
			// @description Get suffix for a given extension
			//	(needed to get the correctly-cased suffix when the file extension is in a different case than assumed)
			// @param ext Wanted extension
			// @return Suffix matching file extension @param ext, or empty string if no suffix corresponding to @param ext is found
			std::string suffixForExtension(std::string ext);
			
			// @description Get a thumbnail of this media
			// @param width Desired width of the thumbnail
			// @param height Desired height of the thumbnail
			// @return The thumbnail
			QPixmap thumbnail(int width, int height);
			
			// @return Path to this media without file extension
			std::filesystem::path path();
			// @return Path to the directory that contains this media
			std::filesystem::path directory() { return _directory; };
			// @return Name of this media (without extension)
			std::string filename() { return _filename; };
			// @return All available suffixes (file extensions) of this media. There is always at least one suffix
			std::set<std::string> suffixes() { return _suffixes; };
			
			// @description Get an available suffix (file extension) for this media
			// @param preferred Which file extension is preferred - if available, the suffix for that extension will be returned.
			// 	If @param preferred is empty or there is no suffix for that extension, the first available suffix will be returned
			std::string suffix(std::string preferred = "");
		
		private:
			std::filesystem::path _directory;
			std::string _filename;
			std::set<std::string> _suffixes;
	};
	
	using MediaPtr = std::shared_ptr<Media>;
	using MediaPtrVector = std::vector<MediaPtr>;
}

#endif

