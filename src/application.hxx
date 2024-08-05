#ifndef PELICAN_APPLICATION_HXX
#define PELICAN_APPLICATION_HXX

#include <map>
#include <memory>
#include <filesystem>

#include <QFileSystemWatcher>
#include <QDir>

#include <easyqt/application.hxx>

#include <argparse/argparse.hpp>

#include "mainwindow.hxx"
#include "media.hxx"

namespace pelican {
	class Application: public easyqt::Application {
		Q_OBJECT
		public:
			Application(int& argc, char **argv);
			void initUI();
			static Application* instance() {
				return qobject_cast<Application*>(easyqt::Application::instance());
			}
			
			void rescanMedias();
			MediaPtrVector medias();
			
			argparse::ArgumentParser arguments;
			
		public slots:
			void mediaDirectoryChanged(const QDir& path);
		
		private:
			QFileSystemWatcher _mediaDirectoryWatcher;
			std::filesystem::path _mediaDirectoryPath = {"/media/frederic/WD-5TB/Kamera/LumixG85/Fotos"};
			std::map<std::string, MediaPtr> _medias;
	};
}

#endif

