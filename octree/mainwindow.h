#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "point.h"
#include "octree.h"

#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    octree *tree;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
