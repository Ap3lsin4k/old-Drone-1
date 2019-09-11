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
    double countSquareW = ceil(latitude/width);
    double countSquareL = ceil(longtitude/length);
    int countSquare=countSquareL*countSquareW;
    qDebug()<<countSquare;
}
