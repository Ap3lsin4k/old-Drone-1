#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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

    double pointXEnd=0,pointXStart=0,pointYEnd=0,pointYStart=0,differentX=0,differentY=0;
    double longtitude,latitude;//довгота //широта

    double length=0,width=0;
public slots:
   void handleDate();

};

#endif // MAINWINDOW_H
