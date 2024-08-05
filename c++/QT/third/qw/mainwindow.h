#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QLabel>
#include <qlabel.h>
#include <QMainWindow>
#include <QPushButton>
class MainWindow : public QMainWindow
{
    //int b;
    Q_OBJECT
private:
    QLabel *bl;
    QPushButton *btn;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
