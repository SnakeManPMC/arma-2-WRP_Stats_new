#include <QtCore/QCoreApplication>
//#include <QDebug>
//#include <QFile>
#include "wrpstatsnew.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	wrpStatsNew(argc, argv);

	return 0;
}
