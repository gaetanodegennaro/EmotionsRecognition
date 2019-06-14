#include "UI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UI w;
	w.setFixedSize(531,352);
	w.setStyleSheet("QMainWindow {background: 'white';}");
	w.show();
	return a.exec();
}
