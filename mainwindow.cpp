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

    connect(ui->pushButton_Search, &QPushButton::clicked, this, &MainWindow::slot_search);

    connect(ui->pushButton_Add, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->detailPage);
    });

    // ---  window 2  ---
    connect(ui->pushButton_Goback, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->defaultPage);
    });

    connect(ui->pushButton_Save, &QPushButton::clicked, this, [&](){
        Contact *newContact = new Contact();
        newContact->name = ui->lineEdit_Name->text();
        newContact->phone= ui->lineEdit_Call->text();
        newContact->birthday = QDate::currentDate();
        newContact->favorite = 0;
        newContact->email= ui->lineEdit_Email->text();
        newContact->SNS = ui->lineEdit_SNS->text();
        newContact->memo = ui->textEdit_Memo->toPlainText();

        newContact->id = QUuid::createUuid();
        // newContact->parent
        Contact *parent = model->getRoot();
        model->addContact(newContact, parent);

        // model->getRoot()->children.append(newContact);
        QMessageBox::information(this, "추가완료", "연락처가 추가되었습니다");
        // ui->treeView_PhoneBook->setModel(model);
        // model->getList() << newContact;
        // qDebug() << newContact->id;
    });

    // connect(ui->checkBox_Favorite, &QCheckBox::clicked, this,  )
}

void MainWindow::slot_search()
{
    SearchDialog(model->getList(), this).exec();
}

MainWindow::~MainWindow()
{}

