#include "mainwindow.h"
#include "compiler/compiler_warnings_control.h"
#include "assert/advanced_assert.h"

DISABLE_COMPILER_WARNINGS
#include <QApplication>
#include <QDebug>
RESTORE_COMPILER_WARNINGS

int main(int argc, char *argv[])
{
	AdvancedAssert::setLoggingFunc([](const char* msg) {
		qDebug() << msg;
	});

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
