# - Try to find the FreeImagePlus library.
#
# The following are set after configuration is done: 
#  FREEIMAGEPLUS_FOUND
#  FREEIMAGEPLUS_INCLUDE_DIRS
#  FREEIMAGEPLUS_LIBRARIES

find_path(FREEIMAGE_INCLUDE_DIR NAMES FreeImage.h)
find_path(FREEIMAGEPLUS_INCLUDE_DIR NAMES FreeImagePlus.h)
find_library(FREEIMAGE_LIBRARY NAMES libfreeimage.so libfreeimage.so.3)
find_library(FREEIMAGEPLUS_LIBRARY NAMES libfreeimageplus.so libfreeimageplus.so.3)

if (NOT ${FREEIMAGE_LIBRARY} EQUAL FREEIMAGE_LIBRARY-NOTFOUND AND NOT ${FREEIMAGE_INCLUDE_DIR} EQUAL FREEIMAGE_INCLUDE_DIR-NOTFOUND)
	message(STATUS "Found FreeImage library at '${FREEIMAGE_LIBRARY}' and headers at '${FREEIMAGE_INCLUDE_DIR}'")
else()
	message(SEND_ERROR "FreeImage library and / or headers not found !")
endif()
if (NOT ${FREEIMAGEPLUS_LIBRARY} EQUAL FREEIMAGEPLUS_LIBRARY-NOTFOUND AND NOT ${FREEIMAGEPLUS_INCLUDE_DIR} EQUAL FREEIMAGEPLUS_INCLUDE_DIR-NOTFOUND)
	message(STATUS "Found FreeImagePlus library at '${FREEIMAGEPLUS_LIBRARY}' and headers at '${FREEIMAGEPLUS_INCLUDE_DIR}'")
else()
	message(SEND_ERROR "FreeImagePlus library and / or headers not found !")
endif()

set(FREEIMAGEPLUS_LIBRARIES "${FREEIMAGEPLUS_LIBRARY};${FREEIMAGE_LIBRARY}")
set(FREEIMAGEPLUS_INCLUDE_DIRS "${FREEIMAGE_INCLUDE_DIR};${FREEIMAGEPLUS_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)
# Handle the QUIETLY and REQUIRED arguments and set the FREEIMAGEPLUS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FreeImagePlus DEFAULT_MSG
								FREEIMAGEPLUS_LIBRARY FREEIMAGE_LIBRARY FREEIMAGEPLUS_INCLUDE_DIR FREEIMAGE_INCLUDE_DIR)

mark_as_advanced(FREEIMAGEPLUS_INCLUDE_DIR FREEIMAGEPLUS_LIBRARY FREEIMAGE_INCLUDE_DIR FREEIMAGE_LIBRARY)
