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
    pointEnd.first=ui->pointXEnd->text().toDouble();//Довгота
    pointEnd.second=ui->pointYEnd_2->text().toDouble();//Широта

    pointStart.first=ui->pointXStart->text().toDouble();
    pointStart.second=ui->pointYStart->text().toDouble();

    pointBase.first=ui->pointXBase->text().toDouble();
    pointBase.second=ui->pointYBase->text().toDouble();

    length=ui->Length->text().toDouble();
    width=ui->Width->text().toDouble();
    if(pointStart.first<pointEnd.first && pointStart.second>pointEnd.second)
    {
        positionPoints=1;//Стартова позиція в лівому верхньому куті
        differentX=pointEnd.first-pointStart.first;//Довгота в градусах
        differentY=pointStart.second-pointEnd.second;//Широта в градусах
    }else if (pointStart.first>pointEnd.first && pointStart.second>pointEnd.second)
    {
        positionPoints=2;//Стартова точка знаходится в правому верхньому куті
        differentX=pointStart.first-pointEnd.first;//Довгота в градусах
        differentY=pointStart.second-pointEnd.second;//Широта в градусах
    }else if (pointStart.first>pointEnd.first && pointStart.second<pointEnd.second)
    {
        positionPoints=3;//Стартова точка знаходится в правому нижньому куті
        differentX=pointStart.first-pointEnd.first;//Довгота в градусах
        differentY=pointEnd.second-pointStart.second;//Широта в градусах

    }else if (pointStart.first<pointEnd.first && pointStart.second<pointEnd.second)
    {
        positionPoints=4;//Стартова точка знаходится в лівому нижньому куті
        differentX=pointEnd.first-pointStart.first;//Довгота в градусах
        differentY=pointEnd.second-pointStart.second;//Широта в градусах
    }

    qDebug()<<"PositionPoints: "<<positionPoints;
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

    double pointX1=pointStart.first+((length/2)/(cos(differentY*3.14/180)*(40075/360)*1000));  // Координата центра першого прямокутника
    double pointY1=pointStart.second-abs((width/2)/(111.32*1000));

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
    double distanceStart=0;
    a[0][0].first=1;  // ми були в початковій координаті
    order=new CoordinateOrder(countSquareLMain,countSquareWMain,length,width);
    order->coordinateOrder(a,0,0,countSquare);

    vector<pair<int,int>> way=order->getWay();
    double differentXEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.second-pointBase.first;
    double differentYEnd=a[way[countSquare-1].first][way[countSquare-1].second].second.first-pointBase.second;

    double latitudeEnd=differentYEnd*111.32*1000;//Широта в метрах
    double longtitudeEnd=cos(differentYEnd*3.14/180)*40075/360*1000*differentXEnd;
    double distanceEnd=sqrt(pow(latitudeEnd,2)+pow(longtitudeEnd,2));


    double differentXStart=a[way[0].first][way[0].second].second.second-pointBase.first;
    double differentYStart=a[way[0].first][way[0].second].second.first-pointBase.second;

    double latitudeStart=differentYStart*111.32*1000;//Широта в метрах
    double longtitudeStart=cos(differentYStart*3.14/180)*40075/360*1000*differentXStart;
    distanceStart=sqrt(pow(latitudeStart,2)+pow(longtitudeStart,2));
    double d=order->getLength()+distanceEnd+distanceStart;



    qDebug()<<QString::number(d,'f',6);
    qDebug()<<countSquare;

}


pair<int,int> MainWindow::choseStart(vector<vector<pair<int,pair<double, double>> > > &a,pair<double,double> &start, pair<double,double> &end, pair<double,double> &base,double &distanceStart)
{
    pair<int,int> position;
    double min=INT_MAX;

    double diffX=0;
    double diffY=0;
    double latitudeS,longtitudeS;
    switch(positionPoints)
    {
        case 1:
        if(base.second > end.second && base.second < end.second && base.first < start.first)//1
        {
            for(int i=0;i<countSquareWMain;++i)
            {
               diffX=abs(base.first-a[i][0].second.first);
               diffY=abs(base.second-a[i][0].second.second);
               latitudeS=diffY*111.32*1000;
               longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
               distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2));
               if (distanceStart<min)
               {
                   min = distanceStart;
                   position.first=i;
               }
            }
            position.second=0;
        }else
        if (base.second > start.second && base.first > start.first && base.first < end.first) //2
        {
            for(int i=0;i<countSquareLMain;++i)
            {
               diffX=abs(base.first-a[0][i].second.first);
               diffY=abs(base.second-a[0][i].second.second);
               latitudeS=diffY*111.32*1000;
               longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
               distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2));
               if (distanceStart<min)
               {
                   min = distanceStart;
                   position.second=i;
               }
               position.first=0;
            }
        }else
        if (base.second > end.second && base.second <= start.second && base.first >= end.first) //3
        {
            for(int i=0;i<countSquareWMain;++i)
            {
               diffX=abs(base.first-a[i][countSquareLMain-1].second.first);
               diffY=abs(base.second-a[i][countSquareLMain-1].second.second);
               latitudeS=diffY*111.32*1000;
               longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
               distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2));
               if (distanceStart<min)
               {
                   min = distanceStart;
                   position.first=i;
               }
               position.second=countSquareLMain-1;
            }
        }else
        if (base.second < start.second && base.first > start.first && base.first < end.first) //4
        {
            for(int i=0;i<countSquareLMain;++i)
            {
               diffX=abs(base.first-a[countSquareWMain-1][i].second.first);
               diffY=abs(base.second-a[countSquareWMain-1][i].second.second);
               latitudeS=diffY*111.32*1000;
               longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
               distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2));
               if (distanceStart<min)
               {
                   min = distanceStart;
                   position.second=i;
               }
               position.first=countSquareWMain-1;
            }
        }else if (base.first<=start.first && base.second>=start.second) //5
        {
            position.first=0;
            position.second=0;
            diffX=abs(base.first-a[position.first][position.second].second.first);
            diffY=abs(base.second-a[position.first][position.second].second.second);
            latitudeS=diffY*111.32*1000;
            longtitudeS=cos(diffY*3.14/180)*40075/360*1000*diffX;
            distanceStart=sqrt(pow(latitudeS,2)+pow(longtitudeS,2));
            return position;
        }else if (base.first>=end.first && base.second>=start.second)//6
        {
            position.first=0;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first>=end.first && base.second<=end.second) //7
        {
            position.first=countSquareWMain-1;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first<=start.first && base.second<=start.second)//8
        {
            position.first=countSquareWMain-1;
            position.second=0;
            return position;
        }
        break;
        case 2:
        if(base.first<end.first && base.second>end.second && base.second<start.second)//1
        {

        }else
        if (base.second>start.second && base.first>end.first && base.first<start.first) //2
        {

        }else
        if (base.first>end.first && base.second>end.second && base.second<start.second) //3
        {

        }else
        if (base.second<start.second && base.first>end.first && base.first<start.first) //4
        {

        }else if (base.first<=end.first && base.second>=start.second) //5
        {
            position.first=0;
            position.second=0;
            return position;
        }else if (base.first>=start.first && base.second>=start.second)//6
        {
            position.first=0;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first>=start.first && base.second<=end.second) //7
        {
            position.first=countSquareWMain-1;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first<=end.first && base.second<=end.second)//8
        {
            position.first=countSquareWMain-1;
            position.second=0;
            return position;
        }
        break;
        case 3:
        if(base.second > start.second && base.second < start.second && base.first < end.first)//1
        {

        }else
        if (base.second > end.second && base.first > end.first && base.first < start.first) //2
        {

        }else
        if (base.second > start.second && base.second <= end.second && base.first >= start.first) //3
        {

        }else
        if (base.second < end.second && base.first > end.first && base.first < start.first) //4
        {

        }else if (base.first<=end.first && base.second>=end.second) //5
        {
            position.first=0;
            position.second=0;
            return position;
        }else if (base.first>=start.first && base.second>=end.second)//6
        {
            position.first=0;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first>=start.first && base.second<=start.second) //7
        {
            position.first=countSquareWMain-1;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first<=end.first && base.second<=end.second)//8
        {
            position.first=countSquareWMain-1;
            position.second=0;
            return position;
        }
        break;
        case 4:
        if(base.first<start.first && base.second>start.second && base.second<end.second)//1
        {

        }else
        if (base.second>end.second && base.first>start.first && base.first<end.first) //2
        {

        }else
        if (base.first>start.first && base.second>start.second && base.second<end.second) //3
        {

        }else
        if (base.second<end.second && base.first>start.first && base.first<end.first) //4
        {

        }else if (base.first<=start.first && base.second>=end.second) //5
        {
            position.first=0;
            position.second=0;
            return position;
        }else if (base.first>=end.first && base.second>=end.second)//6
        {
            position.first=0;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first>=end.first && base.second<=start.second) //7
        {
            position.first=countSquareWMain-1;
            position.second=countSquareLMain-1;
            return position;
        }else if (base.first<=start.first && base.second<=start.second)//8
        {
            position.first=countSquareWMain-1;
            position.second=0;
            return position;
        }
        break;
        }
}
