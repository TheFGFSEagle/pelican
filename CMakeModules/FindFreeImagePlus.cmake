# - Try to find the FreeImagePlus library.
#
# The following are set after configuration is done: 
#  FREEIMAGEPLUS_FOUND
#  FREEIMAGEPLUS_INCLUDE_DIRS
#  FREEIMAGEPLUS_LIBRARIES

find_path(FREEIMAGEPLUS_INCLUDE_DIR NAMES FreeImagePlus.h)
find_library(FREEIMAGEPLUS_LIBRARY NAMES libfreeimageplus.so libfreeimageplus.so.3)

message(STATUS "Found FreeImagePlus library at '${FREEIMAGEPLUS_LIBRARY}' and headers at '${FREEIMAGEPLUS_INCLUDE_DIR}'")

set(FREEIMAGEPLUS_LIBRARIES ${FREEIMAGEPLUS_LIBRARY})
set(FREEIMAGEPLUS_INCLUDE_DIRS ${FREEIMAGEPLUS_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# Handle the QUIETLY and REQUIRED arguments and set the FREEIMAGEPLUS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FreeImagePlus DEFAULT_MSG
								FREEIMAGEPLUS_LIBRARY FREEIMAGEPLUS_INCLUDE_DIR)

mark_as_advanced(FREEIMAGEPLUS_INCLUDE_DIR FREEIMAGEPLUS_LIBRARY)
