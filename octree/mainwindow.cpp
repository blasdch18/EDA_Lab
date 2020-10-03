#include "mainwindow.h"
#include "point.h"
#include "octree.h"



MainWindow::~MainWindow()
{
    delete tree;
}

void MainWindow::drawSun()
{
    glPushMatrix();
    glTranslatef(cSphere.x,cSphere.y,cSphere.z);
    glScalef(1,1,1);

    GLUquadricObj *quadric=gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    glColor3f(1,1,0);

    gluQuadricDrawStyle(quadric,GLU_SILHOUETTE);

    //gluSphere(quadric, 0.4, 50,50);

    gluDeleteQuadric(quadric);
    glPopMatrix();
}

bool MainWindow::pointIN(point a){
    if(sqrt(pow((cSphere.x-a.x),2)+pow((cSphere.y-a.y),2)+pow((cSphere.z-a.z),2)) <= pow(radio,2)){

         qDebug()<< "DENTRO "<< endl;
         return true;
    }
     //qDebug()<< sqrt(pow((cSphere.x-a.x),2)+pow((cSphere.y-a.y),2)+pow((cSphere.z-a.z),2)) << "AFUERA "<< endl;
    return false;
}
bool MainWindow::pointC(point a,point max, point min){
    if(a.x >= min.x and a.y >= min.y and a.z >= min.z and
       a.x <= max.x and a.y <= max.y and a.z <= max.z){


         return true;
    }
    return false;
}
bool MainWindow::circleInt(point max, point min){
    if(pointIN(max) and pointIN(min)
      and pointIN(point(max.x,max.y,min.z)) and pointIN(point(min.x,max.y,max.z))
      and pointIN(point(max.x,min.y,max.z)) and pointIN(point(max.x,min.y,min.z))
      and pointIN(point(min.x,max.y,min.z)) and pointIN(point(min.x,min.y,max.z)) )
    {
        qDebug()<< "todos "<< endl;
      return true;
    }
    qDebug()<< "ninguno "<< endl;
    return false;

}
bool MainWindow::circleInt2(point max, point min){
    if(pointIN(max) or pointIN(min)
      or pointIN(point(max.x,max.y,min.z)) or pointIN(point(min.x,max.y,max.z))
      or pointIN(point(max.x,min.y,max.z)) or pointIN(point(max.x,min.y,min.z))
      or pointIN(point(min.x,max.y,min.z)) or pointIN(point(min.x,min.y,max.z)) )
    {
         qDebug()<< "alguno "<< endl;
      return true;
    }
    return false;

}

MainWindow::MainWindow(QWidget *parent)
{

    setSurfaceType(QWindow::OpenGLSurface);


    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);

    setFormat(format);

    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();

    context->makeCurrent(this);
    openGLFunctions = context->functions();

    //qDebug() << "lo creare" ;
    //point min(-1.0,-1.0,-1.0);
    //point max(1.0,1.0,1.0);

    tree = nullptr;
    tree = new octree(-1.0,-1.0,-1.0,1.0,1.0,1.0);

    cCircle.x = 0.0;
    cCircle.y = 0.0;
    cCircle.z = 0.0;

    cSphere.x = 0.0;
    cSphere.y = 0.0;
    cSphere.z = 0.0;

    angle= 0.2;

    zoomScale = 1.0;

    pressLB = false;
    radio = 0.5;
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    //qDebug() << ev->x() << " - " << ev-> y();

    //if(ev->button() == Qt::RightButton){
        cCircle.x = float(ev->x())/float(this->width())-0.5;
        cCircle.y = float(ev->y())/float(this->height())-0.5;
         cCircle.x *= 2;
       cCircle.y *= -2;

       cSphere.x = cCircle.x ;
       cSphere.y = cCircle.y ;

    //}
    update();
}

void MainWindow::wheelEvent(QWheelEvent *ev){


    //angle += (ev->delta()/3000.0);
    //if(angle < 0) angle = 0.0001;
    //update();

    QPoint numDegrees = ev->angleDelta();
    if (numDegrees.y() < 0)  zoomScale = zoomScale/1.1;
    if (numDegrees.y() > 0)  zoomScale = zoomScale*1.1;
    update(); // call paintGL()



}
void MainWindow::pushPoint(octree **p)
{
    if((*p)->punto){
        for(int i=0; i<(*p)->children.size();i++){
            pSelec.push_back((*p)->children[i]->punto);
        }
    }else{
        pushPoint(&(*p)->children[0]);
        pushPoint(&(*p)->children[1]);
        pushPoint(&(*p)->children[2]);
        pushPoint(&(*p)->children[3]);
        pushPoint(&(*p)->children[4]);
        pushPoint(&(*p)->children[5]);
        pushPoint(&(*p)->children[6]);
        pushPoint(&(*p)->children[7]);
    }
}
void MainWindow::findC(octree **p){

    //qDebug()<< "comenzOOOOOOOp" <<endl;

    if(circleInt((*p)->max,(*p)->min)){
        pushPoint(p);

        return;
    }


    if(circleInt2((*p)->max,(*p)->min) or
            pointC(point(cSphere.x,cSphere.y,cSphere.z),(*p)->max,(*p)->min) ){

        if((*p)->punto){
            for(int i=0;i<(*p)->children.size();i++){
                if(pointIN(*(*p)->children[i]->punto))
                    pSelec.push_back((*p)->children[i]->punto);
            }
            return;
        }else{
            findC(&(*p)->children[0]);
            findC(&(*p)->children[1]);
            findC(&(*p)->children[2]);
            findC(&(*p)->children[3]);
            findC(&(*p)->children[4]);
            findC(&(*p)->children[5]);
            findC(&(*p)->children[6]);
            findC(&(*p)->children[7]);

        }
    }

}
void MainWindow::keyPressEvent(QKeyEvent *ev){
    //qDebug() << "key: " << ev->key();
    if(ev->key() == 70){

        pSelec.clear();

        //qDebug() << "buscar";
        findC(&tree);

        /*
        for(int i=0;i<pSelec.size();i++){
            qDebug() << pSelec[i]->x << " - " << pSelec[i]->y ;
        }
        */
        //qDebug() << "----" <<pSelec.size()<< " puntos." ;
        update();
    }
}
void MainWindow::mousePressEvent(QMouseEvent *ev)
{

    float x_p = float(ev->x())/float(this->width())-0.5;
    float y_p = float(ev->y())/float(this->height())-0.5;

    pointsW.push_back(point(x_p*2,y_p*-2));

    tree->insert(x_p*2,y_p*-2,0);

    linesA.clear();
    linesB.clear();

    printQT(&tree);
    update();

}
void MainWindow::initializeGL()
{
    resizeGL(this->width(),this->height());

}


void MainWindow::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0,0,w,h);

   qreal aspectratio = qreal(w)/qreal(h);
   glOrtho(-1* aspectratio,1*aspectratio,-1,1,1,-1);


}



void MainWindow::paintGL()
{

    glClearColor(255, 255, 255, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glScaled(zoomScale, zoomScale, zoomScale);
    //qDebug() << zoomScale ;
    glPointSize(3);


    gluPerspective(45.0,1.0,1.0,100.0);
    glTranslatef(0,0,-6);


    glRotatef(cCircle.x*100,0,1,0);
    glRotatef(cCircle.y*100,1,0,0);

    pressLB = false;

    drawSun();


    glBegin(GL_POINTS);
    glColor3d(0,0,255);
    for(int i=0;i<int(pointsW.size());i++){
        //qDebug() <<pointsW[i].first<< "paint " << pointsW[i].second<< "size" <<pointsW.size() ;
        glVertex3d(pointsW[i].x,pointsW[i].y,pointsW[i].z);
    }
    glEnd();

    qDebug() <<pSelec.size() << "puntos selec " << endl;

    glBegin(GL_POINTS);
    glColor3d(0,255,0);
    for(int i=0;i<int(pSelec.size());i++){

        glVertex3d(pSelec[i]->x,pSelec[i]->y,pSelec[i]->z);
    }
    glEnd();


    glBegin(GL_LINES);
    glColor3d(255,0,0);
    //qDebug() <<" gh "<<linesA.size() ;
    for(int i=0;i<int(linesA.size());i++){

        glVertex3d(linesA[i].x,linesA[i].y,linesA[i].z);
        glVertex3d(linesB[i].x,linesB[i].y,linesB[i].z);
    }

    glEnd();



    //qDebug() << x_m << " pa " << y_m ;line
    //drawHollowCircle(cCircle.x,cCircle.y,angle);

    glFlush();


}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    resizeGL(this->width(),this->height());
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    paintGL();

}

void MainWindow::printQT(octree **quad)
{


    if(!((*quad)->punto)){

        float midX = ((*quad)->max.x + (*quad)->min.x)/2;
        float midY = ((*quad)->max.y + (*quad)->min.y)/2;
        float midZ = ((*quad)->max.z + (*quad)->min.z)/2;

        linesA.push_back(point((*quad)->min.x,midY,midZ));
        linesB.push_back(point((*quad)->max.x,midY,midZ));

        linesA.push_back(point(midX,midY,(*quad)->min.z));
        linesB.push_back(point(midX,midY,(*quad)->max.z));

        linesA.push_back(point(midX,(*quad)->min.y,midZ));
        linesB.push_back(point(midX,(*quad)->max.y,midZ));

        linesA.push_back(point((*quad)->min.x,midY,(*quad)->max.z));
        linesB.push_back(point((*quad)->max.x,midY,(*quad)->max.z));

        linesA.push_back(point(midX,(*quad)->min.y,(*quad)->max.z));
        linesB.push_back(point(midX,(*quad)->max.y,(*quad)->max.z));


        linesA.push_back(point((*quad)->min.x,midY,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,midY,(*quad)->min.z));

        linesA.push_back(point(midX,(*quad)->min.y,(*quad)->min.z));
        linesB.push_back(point(midX,(*quad)->max.y,(*quad)->min.z));

        linesA.push_back(point((*quad)->min.x,midY,(*quad)->min.z));
        linesB.push_back(point((*quad)->min.x,midY,(*quad)->max.z));

        linesA.push_back(point((*quad)->max.x,midY,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,midY,(*quad)->max.z));


        linesA.push_back(point(midX,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point(midX,(*quad)->max.y,(*quad)->max.z));
        linesA.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->max.z));
        linesA.push_back(point((*quad)->max.x,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->max.y,(*quad)->max.z));

        linesA.push_back(point(midX,(*quad)->min.y,(*quad)->min.z));
        linesB.push_back(point(midX,(*quad)->min.y,(*quad)->max.z));
        linesA.push_back(point((*quad)->min.x,(*quad)->min.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->min.x,(*quad)->min.y,(*quad)->max.z));
        linesA.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->max.z));


        linesA.push_back(point(midX,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point(midX,(*quad)->max.y,(*quad)->max.z));

        linesA.push_back((*quad)->min);
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->min.z));

        linesA.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->max.y,(*quad)->min.z));

        linesA.push_back(point((*quad)->min.x,(*quad)->max.y,midZ));
        linesB.push_back(point((*quad)->max.x,(*quad)->max.y,midZ));

        linesA.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->max.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->max.y,(*quad)->max.z));

        linesA.push_back(point((*quad)->min.x,(*quad)->min.y,midZ));
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,midZ));

        linesA.push_back(point((*quad)->min.x,(*quad)->min.y,(*quad)->max.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->max.z));

        linesA.push_back((*quad)->min);
        linesB.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->min.z));

        linesA.push_back(point((*quad)->min.x,(*quad)->min.y,midZ));
        linesB.push_back(point((*quad)->min.x,(*quad)->max.y,midZ));

        linesA.push_back(point((*quad)->min.x,(*quad)->min.y,(*quad)->max.z));
        linesB.push_back(point((*quad)->min.x,(*quad)->max.y,(*quad)->max.z));

        linesA.push_back((*quad)->max);
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->max.z));


        linesA.push_back(point((*quad)->max.x,(*quad)->max.y,midZ));
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,midZ));
        linesA.push_back(point((*quad)->max.x,(*quad)->max.y,(*quad)->min.z));
        linesB.push_back(point((*quad)->max.x,(*quad)->min.y,(*quad)->min.z));


            printQT(&((*quad)->children[0]));
            printQT(&((*quad)->children[1]));
            printQT(&((*quad)->children[2]));
            printQT(&((*quad)->children[3]));
            printQT(&((*quad)->children[4]));
            printQT(&((*quad)->children[5]));
            printQT(&((*quad)->children[6]));
            printQT(&((*quad)->children[7]));

    }
}
