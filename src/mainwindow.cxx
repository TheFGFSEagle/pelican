#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>

#include <iostream>

#include "application.hxx"
#include "menubar.hxx"
#include "uiloader.hxx"

namespace pelican {
	MainWindow::MainWindow() {
	}
	
	MainWindow::~MainWindow() {
		delete MenuBar::instance("pelican::GlobalMenuBar");
		delete mainWidget;
	}
	
	void MainWindow::initUI() {
		setWindowTitle("Pelican");
		loadWidgetFromFile<MainWindow>("res:ui/mainwindow.ui");
		//mainWidget = new QWidget();
		//QVBoxLayout mainLayout;
		//mainWidget->setLayout(&mainLayout);
		//setCentralWidget(mainWidget);
		//statusBar();
	}
}

