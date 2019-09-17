#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <cmath>
#include <iomanip>
#include <vector>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(ui->formLayout);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::handleDate);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleDate()
{
    pointXEnd=ui->pointXEnd->text().toDouble();//Довгота
    pointYEnd=ui->pointYEnd_2->text().toDouble();//Широта

    pointXStart=ui->pointXStart->text().toDouble();
    pointYStart=ui->pointYStart->text().toDouble();
    length=ui->Length->text().toDouble();
    width=ui->Width->text().toDouble();
    differentX=pointXEnd-pointXStart;//Довгота в градусах
    differentY=pointYEnd-pointYStart;//Широта в градусах
    latitude=differentY*111.32*1000;//Широта в метрах
    longtitude=cos(differentY*3.14/180)*40075/360*1000*differentX;//Довгота в метрах
    qDebug()<<"Latitude v metrax, longtitude: "<<latitude<<" "<<longtitude;
    unsigned int countSquareWMain, countSquareLMain;
    double countSquareWDouble = abs(latitude/width), countSquareLDouble = abs(longtitude/length);
    double countSquareWTrunc = trunc(countSquareWDouble), countSquareLTrunc = trunc(countSquareLDouble);
    double difference = countSquareWDouble - countSquareWTrunc;
    if (difference>0)
    {
        countSquareWMain = countSquareWTrunc+1;
    }
    else {
        countSquareWMain = countSquareWTrunc;
    }
    difference = countSquareLDouble - countSquareLTrunc;
    if (difference>0)
    {
        countSquareLMain = countSquareLTrunc+1;
    }
    else {
        countSquareLMain = countSquareLTrunc;
    }

    qDebug()<<latitude/width<<" "<<longtitude/length;
    double pointX1=pointXStart+((length/2)/(cos(differentY*3.14/180)*(40075/360)*1000));
    double pointY1=pointYStart-abs((width/2)/(111.32*1000));

    std::pair<double,double> *defpair=new std::pair<double,double> () ;
            defpair->first=pointX1;
            defpair->second=pointY1;
    std::vector<std::pair<double, double>> def(countSquareWMain,*defpair) ;
    std::vector<std::vector<std::pair<double, double>>> a(countSquareLMain,def);

    qDebug()<<"1:"<<QString::number(pointY1,'f',6)+","+QString::number(pointX1,'f',6);
    for(unsigned int i=0;i<countSquareLMain;++i)
    {



        if(i!=0)
        {
          a[i][0].first+=(length)/(cos(differentY*3.14/180)*(40075/360)*1000);
        }
        a[i][0].second=pointY1;
        for (unsigned int j=0;j<countSquareWMain;++j)
        {
            if(j!=0)
            a[i][j].second-=abs((width)/(111.32*1000));
            qDebug()<<QString::number(a[i][j].second,'f',6)+","+QString::number(a[i][j].first,'f',6);
        }
    }

    qDebug()<<"countW double: "<<countSquareWDouble<<"countL"<<countSquareLDouble;
    qDebug()<<"countW main: "<<countSquareWMain<<"countL"<<countSquareLMain;
    double  countSquare=countSquareLMain*countSquareWMain;
    qDebug()<<countSquare;
}
