#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <cmath>
#include <iomanip>
#include <vector>
#include "coordinateorder.h"

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

    pointXBase=ui->pointXBase->text().toDouble();
    pointYBase=ui->pointYBase->text().toDouble();

    length=ui->Length->text().toDouble();
    width=ui->Width->text().toDouble();

    differentX=pointXEnd-pointXStart;//Довгота в градусах
    differentY=pointYEnd-pointYStart;//Широта в градусах

    latitude=differentY*111.32*1000;//Широта в метрах
    longtitude=cos(differentY*3.14/180)*40075/360*1000*differentX;//Довгота в метрах

    qDebug()<<"Latitude v metrax, longtitude: "<<latitude<<" "<<longtitude;

    countSquareWDouble = abs(latitude/width);
    countSquareLDouble = abs(longtitude/length);

    countSquareWTrunc = trunc(countSquareWDouble);
    countSquareLTrunc = trunc(countSquareLDouble);

    difference = countSquareWDouble - countSquareWTrunc;

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

    double pointX1=pointXStart+((length/2)/(cos(differentY*3.14/180)*(40075/360)*1000));  // Координата центра першого прямокутника
    double pointY1=pointYStart-abs((width/2)/(111.32*1000));

    pair<int,pair<double,double>> *defpair=new pair<int,pair<double,double>>();
    defpair->first=0;
    vector<pair<int,pair<double, double>>> def(countSquareLMain,*defpair) ;  // {ми там були, (Latitude1, Longtitude1)}, {чи ми там були, (Latitude2, Longtitude2)}
    vector<vector<pair<int, pair<double, double>>>> a(countSquareWMain,def);
    a[0][0].second.first=pointY1;
    a[0][0].second.second=pointX1;
    qDebug()<<"countW double: "<<countSquareWDouble<<"countL"<<countSquareLDouble;
    qDebug()<<"countW main: "<<countSquareWMain<<"countL"<<countSquareLMain;

//    qDebug()<<"1:"<<QString::number(pointY1,'f',6)+","+QString::number(pointX1,'f',6);
    for(unsigned int i=0;i<countSquareWMain;++i)
    {
        if(i!=0)
        {
          a[i][0].second.first=a[i-1][0].second.first-abs((width)/(111.32*1000));;
        }
        a[i][0].second.second=pointX1;
        for (unsigned int j=0;j<countSquareLMain;++j)
        {
            if(j!=0)
            {
                a[i][j].second.second=a[i][j-1].second.second+(length)/(cos(differentY*3.14/180)*(40075/360)*1000);

            }
            a[i][j].second.first=a[i][0].second.first;
            qDebug()<<QString::number(a[i][j].second.first,'f',6)+", "+QString::number(a[i][j].second.second,'f',6);
        }
    }



    int countSquare=countSquareLMain*countSquareWMain;
    a[0][0].first=1;  // ми були в початковій координаті
    order=new CoordinateOrder(countSquareLMain,countSquareWMain,length,width);
    order->coordinateOrder(a,0,0,countSquare);

    vector<pair<int,int>> way=order->getWay();
    double differentXEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.second-pointXBase;
    double differentYEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.first-pointYBase;

    double latitudeEnd=differentYEnd*111.32*1000;//Широта в метрах
    double longtitudeEnd=cos(differentYEnd*3.14/180)*40075/360*1000*differentXEnd;
    double distanceEnd=sqrt(pow(latitudeEnd,2)+pow(longtitudeEnd,2));


    double differentXStart=a[way[0].first][way[0].second].second.second-pointXBase;
    double differentYStart=a[way[0].first][way[0].second].second.first-pointYBase;

    double latitudeStart=differentYStart*111.32*1000;//Широта в метрах
    double longtitudeStart=cos(differentYStart*3.14/180)*40075/360*1000*differentXStart;
    double distanceStart=sqrt(pow(latitudeStart,2)+pow(longtitudeStart,2));
    double d=order->getLength()+distanceEnd+distanceStart;
    qDebug()<<QString::number(d,'f',6);
    qDebug()<<countSquare;
    vutr = ui->vutr->text().toDouble();
    vusot= ui->vusot->text().toDouble();
    vutrnafoto= ui->vutrnafoto->text().toDouble();
    double pal=d*vutr + vutrnafoto*countSquare;
    qDebug()<<QString::number(pal,'f',6);


}
