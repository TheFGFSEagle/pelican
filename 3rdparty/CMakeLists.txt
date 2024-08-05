add_subdirectory(argparse)
set(ENABLE_TESTING OFF)
add_subdirectory(easyqt)
unset(ENABLE_TESTING)
if (NOT TARGET pugixml)
	add_subdirectory(pugixml)
endif()

