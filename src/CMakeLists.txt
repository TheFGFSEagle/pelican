add_executable(pelican
	application.cxx
	commands.cxx
	exifutils.cxx
	main.cxx
	mainwindow.cxx
	media.cxx
	mediainfopane.cxx
	mediashowarea.cxx
	mediaview.cxx
	menubar.cxx
	thumbnailmanager.cxx
	uiloader.cxx
)
target_include_directories(
	pelican
	PUBLIC
		${FREEIMAGEPLUS_INCLUDE_DIRS}
		${PYSTRING_INCLUDE_DIRS}
)
target_link_libraries(
	pelican
	Qt::Widgets
	argparse
	easyqt
	exiv2lib
	fmt
	pugixml
	${FREEIMAGEPLUS_LIBRARIES}
	${PYSTRING_LIBRARIES}
)

install(
	TARGETS pelican
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
