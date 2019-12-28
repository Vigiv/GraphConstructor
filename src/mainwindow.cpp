#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(100, 100, 1280, 720);
    setWindowTitle("Graph Constructor");
}

MainWindow::~MainWindow()
{
}

