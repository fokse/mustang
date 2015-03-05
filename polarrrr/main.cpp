#include <QApplication>
#include "mainwindow.h"
#include <QtGui>
#include <qcustomplot.h>
using namespace::std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow imgDraw;
    imgDraw.show();
    return a.exec();
}

