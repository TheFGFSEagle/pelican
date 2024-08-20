#include <exiv2/exiv2.hpp>

#include "application.hxx"

int main(int argc, char *argv[]) {
	Exiv2::XmpParser::initialize();
	::atexit(Exiv2::XmpParser::terminate);
	
	pelican::Application app(argc, argv);
	app.initUI();
	return app.exec();
}

