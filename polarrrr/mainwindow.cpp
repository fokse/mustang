#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QtGui>
#include <QStringList>
#include <QWidget>
#include <QFile>
#include <QtCore/qmath.h>
#include <QTextStream>

MainWindow::MainWindow(QWidget* pwgt/*=0*/) : QMainWindow(pwgt), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    customPlot = new QCustomPlot(this);
      widget = new QCustomPlot(this);

        paintRect();
        QPixmap pix("C:/rectwithoutgraf.bmp");//совмещение картинок!!
        QImage img("C:/A.bmp");
        int pixx=pix.height()/2;
        qDebug()<<pix.height();
        int pixy=pix.width()/2;
        QMatrix mat;
        QPainter *paint = new QPainter(this);
        paint->begin(&pix);
        paint->begin(&img);
        mat.translate(pixx,pixy);
        int angle=0;
        QString name, etc, a, aname, fname, afname, fileetc;

        fileetc=".txt";
        fname="C:/A/file-";

        QImage openator;
        etc=".bmp";
        aname="C:/A/SWG";
         double avermass[40];

         QString fRadius,fPolarAngle,fEtc,fNameRad,fNameAng, fRatio, fNameRatio;
         fRadius="C:/A/RADIUS-";
         fPolarAngle="C:/A/POLARANGLE-";
         fRatio="C:/A/RATIO-";

         fEtc=".txt";


         QVector <int> vecX;
         QVector <int> vecY;
         QVector <double> polarAngle;
         QVector <double> radius;
         QVector <double> ratio;

         QVector<int> summ;

         int mass[72];
         int i=0;
//         drawReference(paint, pix, fileetc,fname,etc,aname,name,afname, a,vecX,vecY);

         while(angle<360)
            {

                vecX.clear();
                vecY.clear();
                ratio.clear();
//             совмещение и прокрутка картинок
            mat.rotate(5);
            mat.translate(-pixx,-pixy);
            paint->setMatrix(mat);
            paint->drawImage(0,0, QImage("C:/A.bmp"));
            name=aname+a.setNum(angle);
            pix.save(name+etc);

            openator.load(name+etc);
            openator.convertToFormat(QImage::Format_Indexed8);

            //запись их значений в файл
            // and drawing in polar
            afname=fname+a.setNum(angle);
            fNameAng=fPolarAngle+a.setNum(angle);
            fNameRad=fRadius+a.setNum(angle);
            fNameRatio=fRatio+a.setNum(angle);
            int s=toFile(afname, fileetc, openator, avermass, 40, vecX, vecY ,summ);

            mass[i]=s;
//            massToPolar(fNameRad,fNameAng, fEtc, polarAngle,radius ,vecX, vecY , ratio, fNameRatio);
            mat.translate(pixx,pixy);
            angle++;
            angle++;
            angle++;
            angle++;
            angle++;
            i++;
        }

         QVector<double> x(360), y(360); // initialize with entries 0..100
         for (int i=0; i<72; ++i)
         {
           x[i] = i; // x goes from -1 to 1
           y[i] = mass[i]; // let's plot a quadratic function
         }
         // create graph and assign data to it:
         ui->widget->addGraph();
         ui->widget->graph(0)->setData(x, y);
         // give the axes some labels:
         ui->widget->xAxis->setLabel("x");
         ui->widget->yAxis->setLabel("y");
         // set axes ranges, so we see all data:
         ui->widget->xAxis->setRange(0, 100);
         ui->widget->yAxis->setRange(200, 230);
         ui->widget->replot();
    setWindowTitle (tr("MUSTANG"));
//          this->setCentralWidget(widget);
    }


void MainWindow::drawReference(QPainter *paint,QPixmap pix,
                               QString fileetc,QString fname, QString etc, QString aname, QString name, QString afname, QString a,
                               QVector<int> &vecX, QVector<int> &vecY)

{

    fileetc=".txt";
    fname="C:/ReferenceA/file-";

    QImage openator;
    etc=".bmp";
    aname="C:/ReferenceA/picture";

        paint->drawImage(0,0, QImage("C:/A.bmp"));
        name=aname+a.setNum(0);
        pix.save(name+etc);

        openator.load(name+etc);
        openator.convertToFormat(QImage::Format_Indexed8);

        //запись их значений в файл
        afname=fname+a.setNum(0);

        //------TO FILE REFERENCE------
        QFile fale(afname+fileetc);
        fale.open(QFile::ReadWrite|QFile::Text);
        QTextStream fileashool(&fale);

        //чтение каждого пикселя
        int h=openator.height();
        int w=openator.width();
        int ashool[h][w];
        for(int j=0;j<h;j++)
        {
//            int summI=0;
            for(int i=0;i<w;i++)
            {
                //получаем Х
                ashool[i][j]=openator.pixel(i,j);
                if(ashool[i][j]==-1)
                {
                    ashool[i][j]=0;
                }
                else
                {ashool[i][j]=1;
            vecX.push_back(i);   // - MAIN VALUE
            vecY.push_back(j);}  // - MAIN VALUE
                fileashool<<ashool[i][j];
                }
            fileashool<<"\n";
        }
        fale.flush();
//        polar(N, vecX, vecY);

}
void MainWindow::paintRect()

{
    QRect rect1(0,0,40,40); //draw рисуем прямоугольник
    QPixmap img1(rect1.size()); //size
    QPainter rect; //paint for rect
    rect.begin(&img1);
    rect.initFrom(this);
    rect.setRenderHint(QPainter::Antialiasing,true);//сглаживание
    rect.setBrush(QBrush(Qt::white)); //zaliva
    rect.setPen(QPen(Qt::NoPen));//kontur
    rect.drawRect(rect1);//draw... wtf without this?!
    rect.end();
    rect.begin(this);
    rect.drawPixmap(0,0,img1);//main draw rect
    rect.end();
    rect.end();
    img1.save("C:/rectwithoutgraf.bmp");
}
int MainWindow::toFile(QString afname, QString fileetc,
                        QImage openator, double *mass, int N,
                        QVector<int> &vecX, QVector<int> &vec , QVector<int> &summ)

{

    QFile fale(afname+fileetc);
    fale.open(QFile::ReadWrite|QFile::Text);
    QTextStream fileashool(&fale);

    //чтение каждого пикселя
    // и перевод его  0 1
    int h=openator.height();
    int w=openator.width();
    int ashool[h][w];
    for(int j=0;j<h;j++)
    {

        for(int i=0;i<w;i++)
        {
            //получаем Х
            ashool[i][j]=openator.pixel(i,j);
            if(ashool[i][j]==-1)
            {
                ashool[i][j]=0;
            }
            else
            {
                ashool[i][j]=1;

        vecX.push_back(i);    // запись в вектор
        vec.push_back(j);
            }

            fileashool<<ashool[i][j];  //запись в файл
            }

        fileashool<<"\n";
    }
    qDebug()<<vecX.size()<<" "<<afname;
    fale.flush();
          int q=vecX.size();
          //   polar(N, vecX, vecY);

          return q;
}

/*
void MainWindow::massToPolar(QString fNameRad,QString fNameAng,QString fEtc,
                             QVector <double> polarAngle,QVector <double> radius,
                             QVector <int> &vecX, QVector <int> &vecY ,
                             QVector <double> ratio,  QString fNameRatio)
{
    QFile coorRatio(fNameRatio+fEtc);
    QFile coordRad(fNameRad+fEtc);
    QFile coordAng(fNameAng+fEtc);
    coorRatio.open(QFile::ReadWrite|QFile::Text);
    coordAng.open(QFile::ReadWrite|QFile::Text);
    coordRad.open(QFile::ReadWrite|QFile::Text);
    QTextStream toFileRatio(&coorRatio);
    QTextStream toFileRad(&coordRad);
    QTextStream toFileAng(&coordAng);
    int N=vecX.size();
    for(int i=0;i<N;i++)
    {
        radius.push_back(qSqrt(vecX[i]*vecX[i]+vecY[i]*vecY[i]));
        polarAngle.push_back(vecY[i]/radius[i]);
        ratio.push_back(radius[i]/polarAngle[i]);
        toFileRatio<<ratio[i]<<"\n";
        toFileAng<<polarAngle[i]<<"  "<<vecY[i]<<"  "<<radius[i]<<"\n";
        toFileRad<<radius[i]<<"  "<<vecX[i]<<"  "<<vecY[i]<<"\n";
    }
    coorRatio.flush();
    coordAng.flush();
    coordRad.flush();

}
*/

/*
void MainWindow::polar( int N, QVector<int> &vecX, QVector<int> &vecY)
{
        // create empty curve objects and add them to customPlot:
        QCPCurve *deltoidRadial = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

        customPlot->addPlottable(deltoidRadial);
        // generate the curve data points:
        QVector<double> x3(N), y3(N);
        for (int i=0; i<N; ++i)
        {
            x3[i] = vecY[i];
            y3[i] =vecX[i];
        }
        // pass the data to the curves:
        deltoidRadial->setData(x3, y3);
        // color the curves:
        QRadialGradient radialGrad(QPointF(310, 180), 200);
        radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
        radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
        radialGrad.setColorAt(1,QColor(120, 20, 240, 10));
        deltoidRadial->setPen(QPen(QColor(100, 20, 240)));
        deltoidRadial->setBrush(QBrush(radialGrad));
        deltoidRadial->setLineStyle(QCPCurve::lsNone);
        deltoidRadial->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
        // set some basic customPlot config:
        customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        customPlot->axisRect()->setupFullAxesBox();
        customPlot->rescaleAxes();
        this->setCentralWidget(customPlot);
}
*/
MainWindow::~MainWindow()
{
      delete ui;

}
