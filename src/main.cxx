#include "application.hxx"

int main(int argc, char *argv[]) {
	pelican::Application app(argc, argv);
	app.initUI();
	return app.exec();
}

