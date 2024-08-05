add_executable(pelican
	application.cxx
	main.cxx
	media.cxx
	mainwindow.cxx
	mediainfopane.cxx
	mediaview.cxx
	menubar.cxx
	thumbnailmanager.cxx
	uiloader.cxx
)
target_link_libraries(
	pelican
	Qt::Widgets
	argparse
	easyqt
	pugixml
)

install(
	TARGETS pelican
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
