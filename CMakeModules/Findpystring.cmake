# - Try to find the pystring library.
#
# The following are set after configuration is done: 
#  PYSTRING_FOUND
#  PYSTRING_INCLUDE_DIRS
#  PYSTRING_LIBRARIES

find_path(PYSTRING_INCLUDE_DIR NAMES pystring/pystring.h)
find_library(PYSTRING_LIBRARY NAMES libpystring.so libpystring.so.0)

if (NOT ${PYSTRING_LIBRARY} EQUAL PYSTRING_LIBRARY-NOTFOUND AND NOT ${PYSTRING_INCLUDE_DIR} EQUAL PYSTRING_INCLUDE_DIR-NOTFOUND)
	set(PYSTRING_INCLUDE_DIR "${PYSTRING_INCLUDE_DIR}/pystring")
	message(STATUS "Found pystring library at '${PYSTRING_LIBRARY}' and headers at '${PYSTRING_INCLUDE_DIR}'")
else()
	message(SEND_ERROR "Pystring library and / or headers not found !")
endif()

set(PYSTRING_LIBRARIES "${PYSTRING_LIBRARY}")
set(PYSTRING_INCLUDE_DIRS "${PYSTRING_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)
# Handle the QUIETLY and REQUIRED arguments and set the PYSTRINGPLUS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(pystring DEFAULT_MSG
								PYSTRING_LIBRARY PYSTRING_INCLUDE_DIR)

mark_as_advanced(PYSTRING_INCLUDE_DIR PYSTRING_LIBRARY)
