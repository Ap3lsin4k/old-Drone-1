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

    double pointXEnd,pointXStart,pointYEnd,pointYStart,differntX,differentY;

public slots:
   void handleDate();

};

#endif // MAINWINDOW_H
