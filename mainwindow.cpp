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
    pointXEnd=ui->pointXEnd->text().toDouble();
    pointYEnd=ui->pointYEnd->text().toDouble();
    pointXStart=ui->pointXStart->text().toDouble();
    pointYStart=ui->poinYStart->text().toDouble();
    length=ui->Length->text().toDouble();
    width=ui->Width->text().toDouble();
    differntX=pointXEnd-pointXStart;
    differentY=pointYEnd-pointYStart;
    latitude=differntX*111.32*1000;
    longtitude=cos(differntX*3.14/180)*40075/360*1000*differentY;
    qDebug()<<"Latitude, longtitude: "<<latitude<<" "<<longtitude;
    double countSquareWMain, countSquareLMain;
    double countSquareWDouble = latitude/width, countSquareLDouble = longtitude/length;
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
