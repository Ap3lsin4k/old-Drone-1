#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <cmath>

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
    differentX=pointXEnd-pointXStart;//Довгота
    differentY=pointYEnd-pointYStart;//Широта
    latitude=differentY*111.32*1000;
    longtitude=cos(differentY*3.14/180)*40075/360*1000*differentX;
    qDebug()<<"Latitude, longtitude: "<<latitude<<" "<<longtitude;
    double countSquareWMain, countSquareLMain;
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

    qDebug()<<"countW double: "<<countSquareWDouble<<"countL"<<countSquareLDouble;
    qDebug()<<"countW main: "<<countSquareWMain<<"countL"<<countSquareLMain;
    double  countSquare=countSquareLMain*countSquareWMain;
    qDebug()<<countSquare;
}
