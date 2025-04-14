#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // QStackedLayout 사용
    // window1 : QTreeView + pushbutton들
    // window2 : 상세 연락처 창


}

MainWindow::~MainWindow()
{
    delete ui;
}
