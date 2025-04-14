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

    connect(ui->treeView_PhoneBook, &QTreeView::clicked, this, [=](const QModelIndex &index){
        currentSelected = index;
    });

    connect(ui->pushButton_Delete, &QPushButton::clicked, this, [=]() {
        if (!currentSelected.isValid())
        {
            QMessageBox::warning(this, "삭제 오류", "삭제할 항목을 먼저 선택하세요.");
            return;
        }

        Contact* contact = static_cast<Contact*>(currentSelected.internalPointer());
        model->removeContact(contact);

        currentSelected = QModelIndex(); // 선택 초기화
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
        newContact->type = DataType::CONTACT;
        newContact->id = QUuid::createUuid();
        Contact *parent = model->getRoot();
        model->addContact(newContact, parent);

        QMessageBox::information(this, "추가완료", "연락처가 추가되었습니다");
    });



    // connect(ui->checkBox_Favorite, &QCheckBox::clicked, this,  )
}

void MainWindow::slot_search()
{
    SearchDialog(model->getList(), this).exec();
}

MainWindow::~MainWindow()
{}

