#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "SearchDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //---------------------------------------------------------
    //테이블 헤더
    // QStandardItemModel* headers;
    // headers->clear();
    // headers->setHorizontalHeaderLabels({"이름", "전화번호"});

    //QString::contains() -> 문자열 포함 여부 검사하는 함수
    //Qt::CaseInsensitive -> 대소문자를 무시하고 검색 (영어 이름일 경우)
    //appendRow(row) -> 테이블에 한 줄 추가



    Contact c = {1, "a", "b", "c", "d"};
    allContacts.push_back(c);
    Contact c1 = {1, "a", "ffff", "c", "d"};
    allContacts.push_back(c1);

    Contact c2 = {1, "b", "b", "c", "d"};
    allContacts.push_back(c2);
    Contact c3 = {1, "b", "ffff", "c", "d"};
    allContacts.push_back(c3);

    connect(ui->pushButton_Search, &QPushButton::clicked, this, &MainWindow::slot_search);
}

void MainWindow::slot_search()
{
    SearchDialog(allContacts, this).exec();
}

MainWindow::~MainWindow()
{}

