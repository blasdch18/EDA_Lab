#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <GL/glu.h>
#include <QMouseEvent>
#include <vector>


#include "point.h"
#include "octree.h"

using namespace std;
class MainWindow : public QOpenGLWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void drawSun();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);

    bool pointIN(point a);

    vector<point> pointsW;


    vector<point> linesA;
    vector<point> linesB;
    vector<point*> pSelec;

    virtual void paintGL();
    octree *tree ;

    void printQT(octree **quad);

    float zoomScale;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);

    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

    void findC(octree **p);
    bool circleInt(point tl, point br);
    bool circleInt2(point tl, point br);


    bool pointC(point a,point max, point min);
    void pushPoint(octree **p);

    point cCircle;
    float angle;
    bool pressLB;
    point cSphere;
    float radio;
private:
    QOpenGLContext *context;
    QOpenGLFunctions *openGLFunctions;
};

#endif // MAINWINDOW_H
