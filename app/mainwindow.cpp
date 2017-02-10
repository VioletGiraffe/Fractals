#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "complex/complex.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	Complex{1, 0} * Complex();
}

MainWindow::~MainWindow()
{
	delete ui;
}
