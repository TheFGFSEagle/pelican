#include <filesystem>

#include <QDir>
#include <QStandardPaths>

#include <argparse/argparse.hpp>

#include "application.hxx"
#include "commands.hxx"
#include "config.hxx"
#include "logging.hxx"
#include "mainwindow.hxx"
#include "mediaview.hxx"

namespace pelican {
	Application::Application(int& argc, char **argv):
		easyqt::Application(argc, argv), arguments("pelican")
	{
		QStringList paths = QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation);
		std::filesystem::path sourceDataPath = std::filesystem::path(SOURCES_PATH) / "data";
		paths.append(sourceDataPath.c_str());
		QDir::setSearchPaths("res", paths);
		
		arguments.add_argument("--log-level")
			.help("Minimum log level (messages with a level lower than this will not be displayed)")
			.default_value("warning");
		
		arguments.parse_args(argc, argv);
		
		easyqt::Logger::instance()->setLogLevel(arguments.get<std::string>("--log-level"));
		LOG(INFO, "log level: " << easyqt::Logger::instance()->logLevel());
		
		addCommands();
	}

	void Application::initUI() {
		auto w = MainWindow::instance();
		w->initUI();
		w->showMaximized();
		
		_mediaDirectoryWatcher.addPath(_mediaDirectoryPath.c_str());
		QObject::connect(&_mediaDirectoryWatcher, &QFileSystemWatcher::directoryChanged, this, &Application::mediaDirectoryChanged);
		rescanMedias();
	}
	
	void Application::mediaDirectoryChanged(const QDir& path) {
		rescanMedias();
	}
	
	void Application::rescanMedias() {
		_medias.clear();
		
		for (const auto& entry: std::filesystem::directory_iterator(_mediaDirectoryPath)) {
			if (!(entry.is_regular_file() || entry.is_symlink())) {
				continue;
			}
			std::filesystem::path stem = entry.path().stem();
			std::filesystem::path ext = entry.path().extension();
			if (_medias.contains(stem)) {
				_medias[stem]->addSuffix(ext);
			} else {
				_medias[stem] = std::make_shared<Media>(_mediaDirectoryPath, stem.string());
				_medias[stem]->addSuffix(ext);
			}
		}
		
		MediaView::instance()->rebuild();
	}
	
	MediaPtrVector Application::medias() {
		MediaPtrVector medias;
		for (const auto& [_, media]: _medias) {
			medias.push_back(media);
		}
		return medias;
	}
}

