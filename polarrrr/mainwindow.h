#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QWidget>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
        QCustomPlot *customPlot;
        QCustomPlot *widget;
protected:
    //virtual void paintEvent(QPaintEvent* pe);
    void paintRect();
    void sovmechenie();
    void polar(int N,  QVector <int> &vecX, QVector <int> &vecY);
   int toFile(QString afname, QString fileetc, QImage openator, double *mass, int N, QVector <int> &vecX, QVector <int> &vec ,QVector<int> &summ);
    void massToPolar(QString fRadius, QString fPolarAngle, QString fEtc,
                     QVector <double> polarAngle, QVector <double> radius,
                     QVector <int> &vecX, QVector <int> &vecY ,
                     QVector <double> ratio, QString fNameRatio);
    void drawReference(QPainter *paint, QPixmap pix,
                       QString fileetc, QString fname, QString etc, QString aname, QString name, QString afname, QString a,
                       QVector<int> &vecX, QVector<int> &vecY);

public:
    MainWindow(QWidget* pwgt = 0);
    virtual ~MainWindow();


};

#endif // MAINWINDOW_H
