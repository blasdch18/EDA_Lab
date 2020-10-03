#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QTextStream>
#include "point.h"
#include <chrono>
#include <iostream>
#include <vector>
#include <GL/glu.h>

using namespace std;

void Reading( QString Filename, QVector<float> &puntos)
{
    QFile file(Filename);
    if(!file.open( QFile::ReadOnly | QFile:: Text) )
    {
        qDebug() << "No se puede";
        return;
    }
    QTextStream in (&file);
    QString text = in.readAll();
    text.remove('v');

    QStringList strList = text.split( QRegExp( "[ ]"), QString::SkipEmptyParts);
    float tmp = 0.5;
    for (int i = 0; i<strList.length(); i++)
    {
        puntos.push_back(strList[i].toFloat()*tmp);
    }
    file.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QVector<float> data;

    QString filename = "~/points/rex.txt";

    Reading(filename, data);
    qDebug() <<"points: "<< data.size()/3;

    for(int i = 0; i < data.size()-3; i=i+3)
    {
        //w.tree->insert
    }

    w.show();
    return a.exec();
}
