#include "QtOpenGLYUV.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtOpenGLYUV w;
	w.show();
	return a.exec();
}
