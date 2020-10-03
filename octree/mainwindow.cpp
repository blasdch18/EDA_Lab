#include "mainwindow.h"
#include "point.h"

MainWindow::MainWindow(QWidget *parent)
{
    tree = nullptr;
    tree = new octree(-1, -1, -1, 1, 1, 1);
}


MainWindow::~MainWindow()
{
    delete tree;
}

