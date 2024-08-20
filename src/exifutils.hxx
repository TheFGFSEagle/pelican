#ifndef PELICAN_EXIFUTILS_HXX
#define PELICAN_EXIFUTILS_HXX

#include <string>
#include <optional>

#include <fmt/core.h>

namespace pelican {
	namespace exif {
		std::optional<double> parseNumber(std::string s);
		std::string formatFocalLength(std::optional<double> focalLength);
		std::string formatShutterSpeed(std::optional<double> duration_s);
		std::string formatAperture(std::optional<double> fNumber);
		std::string formatISO(std::optional<double> iso);
	}
}

#endif

