#include <QFile>
#include <QSplitter>

#include <easyqt/logging.hxx>

#include "mainwindow.hxx"
#include "mediaview.hxx"
#include "mediainfopane.hxx"
#include "menubar.hxx"
#include "uiloader.hxx"

namespace pelican {
	QWidget* UiLoader::createWidget(const QString& widgetName, QWidget* parentWidget, const QString& name) {
		LOG(DEBUG, "pelican::UiLoader::createWidget(widgetName=" << std::quoted(widgetName.toStdString()) << ", name=" << std::quoted(name.toStdString()) << ")");
		QWidget* w;
		if (widgetName == "pelican::MenuBar") {
			w = MenuBar::instance(name.toStdString());
		} else if (widgetName == "pelican::MainWindow") {
			w = MainWindow::instance();
		} else if (widgetName == "pelican::MediaView") {
			w = MediaView::instance();
		} else if (widgetName == "pelican::MediaInfoPane") {
			w = MediaInfoPane::instance();
		} else {
			w = easyqt::UiLoader::createWidget(widgetName, parentWidget, name);
		}
		if (!w) {
			LOG(ERROR, "Unable to create widgets of type '"<< widgetName.toStdString() << "' with name '" << name.toStdString() << "' !")
			return nullptr;
		}
		w->setObjectName(name);
		w->setParent(parentWidget);
		return w;
	}
}

