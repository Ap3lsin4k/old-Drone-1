#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "coordinateorder.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CoordinateOrder *order;
    double pointXEnd=0,pointXStart=0,pointYEnd=0,pointYStart=0,pointXBase=0,pointYBase=0,differentX=0,differentY=0;
     double countSquareWDouble,countSquareWTrunc,difference,countSquareLDouble,countSquareLTrunc;
    double longtitude=0,latitude=0;//довгота //широта
    int countSquareWMain, countSquareLMain;
    double length=0,width=0;
public slots:
   void handleDate();

};

#endif // MAINWINDOW_H
