#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "SearchDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // treeView = new QTreeView(this);
    model = new ContactModel(this);

    ui->treeView_PhoneBook->setModel(model);
    ui->treeView_PhoneBook->setHeaderHidden(false); // 헤더 보이기
    // setCentralWidget(treeView); // 메인창에 트리뷰 넣기



    // Contact c = {1, "a", "b", "c", "d"};
    // allContacts.push_back(c);
    // Contact c1 = {1, "a", "ffff", "c", "d"};
    // allContacts.push_back(c1);

    // Contact c2 = {1, "b", "b", "c", "d"};
    // allContacts.push_back(c2);
    // Contact c3 = {1, "b", "ffff", "c", "d"};
    // allContacts.push_back(c3);

    connect(ui->pushButton_Search, &QPushButton::clicked, this, &MainWindow::slot_search);
}

void MainWindow::slot_search()
{
    SearchDialog(model->getList(), this).exec();
}

MainWindow::~MainWindow()
{}

