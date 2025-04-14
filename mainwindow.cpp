#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
// <<<<<<< Updated upstream
    ui->setupUi(this);

    //---------------------------------------------------------
    //테이블 헤더
    QStandardItemModel* headers;
    headers->clear();
    headers->setHorizontalHeaderLabels({"이름", "전화번호"});

    //QString::contains() -> 문자열 포함 여부 검사하는 함수
    //Qt::CaseInsensitive -> 대소문자를 무시하고 검색 (영어 이름일 경우)
    //appendRow(row) -> 테이블에 한 줄 추가
    for(const Contact& c: allContacts){
        if(c.name.contains(keyword, Qt::CaseInsensitive)){
            QList<QStandardItem*> row; //한 줄을 구성할 셀 리스트
            row << QStandardItem(c.name);
            row << QStandardItem(c.phone);
            headers->appendRow(row);
        }
    }



}

MainWindow::~MainWindow()
{}

