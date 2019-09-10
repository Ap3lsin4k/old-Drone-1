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
    differntX=pointXEnd-pointXStart;
    differentY=pointYEnd-pointYStart;
     qDebug()<<differntX<<" "<<differentY;
    qDebug()<<differntX*111.32*1000<<" "<<cos(differntX*3.14/180)*40075/360*1000*differentY;
}
