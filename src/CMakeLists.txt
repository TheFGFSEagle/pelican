add_executable(pelican
	application.cxx
	commands.cxx
	main.cxx
	media.cxx
	mainwindow.cxx
	mediainfopane.cxx
	mediaview.cxx
	menubar.cxx
	thumbnailmanager.cxx
	uiloader.cxx
)
target_include_directories(
	pelican
	PUBLIC ${FREEIMAGEPLUS_INCLUDE_DIRS}
)
target_link_libraries(
	pelican
	Qt::Widgets
	argparse
	easyqt
	pugixml
	${FREEIMAGEPLUS_LIBRARIES}
)

install(
	TARGETS pelican
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
