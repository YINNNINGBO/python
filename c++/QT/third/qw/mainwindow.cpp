#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    bl = new QLabel("helloworld",this);
    btn  = new QPushButton("退出",this);
    btn-> setGeometry(10,30,50,50);
    /*btn对象发出clicked() 信号，MainWindow对象接受该信号，
     * 调用自身的成员的的特殊处理信号，完成信号处理*/
    connect(btn,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow() {}
