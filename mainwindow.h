#ifndef MAINWINDOW_H
#define MAINWINDOW_
#include <QMainWindow>// Функції для окна и сам класс окно
#include <QDebug>// замість cout
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
    pair<int,int> choseStart(vector<vector<pair<int,pair<double, double>> > > &a,pair<double,double> &start, pair<double,double> &end, pair<double,double> &base,double &distanceStart);
    double differentX=0,differentY=0,height=0;
    pair<double,double> pointEnd, pointStart,pointBase;
    double countSquareWDouble,countSquareWTrunc,difference,countSquareLDouble,countSquareLTrunc;
    double longtitude=0,latitude=0;//довгота //широта
    double vutr=0; //Витрати на політ
    double vusot=0; //Висота польоту
    double vutrnafoto=0;//витрати на політ
    double focusDistance,horizontalAngel, verticalAngel;
    int countSquareWMain, countSquareLMain;
    int positionPoints;//в Ростіка на телефоні або ТЮІ 2019
    double length=0,width=0;
public slots:
   void handleDate();

};

#endif // MAINWINDOW_H
