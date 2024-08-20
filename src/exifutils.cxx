#include <cmath> // std::round, std::stod
#include <iomanip> // std::quoted

#include <pystring.h>

#include <easyqt/logging.hxx> 

#include "exifutils.hxx"

std::optional<double> _stod(std::string s) {
	std::optional<double> v = std::nullopt;
	try {
		v = std::stod(s);
	} catch (std::invalid_argument& e) {
		LOG(ERROR, "Parsing floating point number from " << std::quoted(s) << " failed");
	}
	return v;
}

namespace pelican {
	namespace exif {
		std::optional<double> parseNumber(std::string s) {
			if (s.empty()) {
				return std::nullopt;
			}
			if (s.find("/") != std::string::npos) {
				const auto ps = pystring::partition(s, "/");
				std::string dividends = ps[0], divisors = ps[2];
				std::optional<double> dividend = _stod(dividends), divisor = _stod(divisors);
				if (dividend && divisor) {
					return *dividend / *divisor;
				} else {
					return std::nullopt;
				}
			} else {
				return _stod(s);
			}
		}
		
		std::string formatFocalLength(std::optional<double> focalLength) {
			if (focalLength == std::nullopt) {
				return "- mm";
			}
			return fmt::format("{:.1f} mm", *focalLength);
		}
		
		std::string formatShutterSpeed(std::optional<double> duration) {
			if (duration == std::nullopt) {
				return "- s";
			}
			if (*duration < 1) {
				int one_by_duration = std::round(1.0 / *duration);
				return fmt::format("1/{:d} s", one_by_duration);
			} else if (*duration < 60) {
				return fmt::format("{:.1f} s", *duration);
			} else {
				return fmt::format("{:.1f} m", (*duration) / 60.0);
			}
		}
		
		std::string formatAperture(std::optional<double> fNumber) {
			if (fNumber == std::nullopt) {
				return "F/-";
			}
			if (std::rint(*fNumber) != *fNumber) {
				return fmt::format("F/{:2.1f}", *fNumber);
			} else {
				return fmt::format("F/{:2.0f}", *fNumber);
			}
		}
		
		std::string formatISO(std::optional<double> iso) {
			if (iso == std::nullopt) {
				return "-";
			}
			return fmt::format("{:.0f}", *iso);
		}
	}
}

