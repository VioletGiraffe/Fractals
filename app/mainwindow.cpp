#include "mainwindow.h"
#include "mandelbrot/cmandelbrotset.h"
#include "mandelbrot/cburningshipset.h"

DISABLE_COMPILER_WARNINGS
#include "ui_mainwindow.h"
RESTORE_COMPILER_WARNINGS

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	ui->fractalWidget->setFractal<CMandelbrotSet>();
}

MainWindow::~MainWindow()
{
	delete ui;
}
