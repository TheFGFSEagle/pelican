#include <QFile>
#include <QSplitter>

#include <easyqt/logging.hxx>

#include "mainwindow.hxx"
#include "mediaview.hxx"
#include "mediainfopane.hxx"
#include "mediashowarea.hxx"
#include "menubar.hxx"
#include "uiloader.hxx"

namespace pelican {
	QWidget* UiLoader::createWidget(const QString& widgetName, QWidget* parentWidget, const QString& name) {
		QWidget* w;
		if (widgetName == "pelican::MenuBar") {
			w = MenuBar::instance(name.toStdString());
		} else if (widgetName == "pelican::MainWindow") {
			w = MainWindow::instance();
		} else if (widgetName == "pelican::MediaView") {
			w = MediaView::instance();
		} else if (widgetName == "pelican::MediaInfoPane") {
			w = MediaInfoPane::instance();
		} else if (widgetName == "pelican::MediaShowArea") {
			w = MediaShowArea::instance();
			w->hide();
		} else {
			w = easyqt::UiLoader::createWidget(widgetName, parentWidget, name);
		}
		if (!w) {
			LOG(ERROR, "Unable to create widget of type '"<< widgetName.toStdString() << "' with name '" << name.toStdString() << "' !")
			return nullptr;
		}
		w->setObjectName(name);
		w->setParent(parentWidget);
		return w;
	}
}

