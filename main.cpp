#include "xmlconverter.h"
#include <QtWidgets/QApplication>
#include <qstylefactory>
#include <QTextCodec>

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)

//
//int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

	QApplication a(__argc, __argv );

	a.setStyle(QStyleFactory::create("Fusion"));
	
	QStringList paths = QCoreApplication::libraryPaths();
	paths.append(".");
	paths.append("imageformats");
	paths.append("platforms");
	paths.append("sqldrivers");
	QCoreApplication::setLibraryPaths(paths);

	xmlconverter w;
	w.show();
	return a.exec();
}
