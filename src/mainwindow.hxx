#ifndef PELICAN_MAINWINDOW_HXX
#define PELICAN_MAINWINDOW_HXX

#include <QMainWindow>

#include "singleton.hxx"

namespace pelican {
	class MainWindow: public Singleton<MainWindow, QMainWindow> {
		Q_OBJECT
		public:
			MainWindow();
			~MainWindow();
			void initUI();
		
		private:
			QWidget* mainWidget;
	};
}

#endif

