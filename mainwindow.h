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
    pair<int,int> choseStart(double startX, double startY, double endX, double endY, double baseX, double baseY);
    double differentX=0,differentY=0;
    pair<double,double> pointEnd, pointStart,pointBase;
    double countSquareWDouble,countSquareWTrunc,difference,countSquareLDouble,countSquareLTrunc;
    double longtitude=0,latitude=0;//довгота //широта
    int countSquareWMain, countSquareLMain;
    int positionPoints;//в Ростіка на телефоні або ТЮІ 2019
    double length=0,width=0;
public slots:
   void handleDate();

};

#endif // MAINWINDOW_H
