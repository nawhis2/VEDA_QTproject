#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "SearchDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    model = new ContactModel(this);

    ui->treeView_PhoneBook->setModel(model);
    ui->treeView_PhoneBook->setHeaderHidden(false); // 헤더 보이기

    connect(ui->pushButton_Search, &QPushButton::clicked, this, &MainWindow::slot_search);

    connect(ui->pushButton_Add, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->detailPage);
        clearDetailWindow();
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

    connect(ui->treeView_PhoneBook, &QTreeView::doubleClicked, this, [=](const QModelIndex &index){

        Contact* contact = static_cast<Contact*>(index.internalPointer());
        if (!contact || contact->type == DataType::GROUP) return;
        ui->stackedWidget->setCurrentWidget(ui->detailPage);

        setDetailWindow(index);
    });


    // ---  window 2  ---
    connect(ui->pushButton_Goback, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->defaultPage);
    });

    connect(ui->pushButton_Save, &QPushButton::clicked, this, [&](){
        addNewContact();
        clearDetailWindow();

        // 즐겨찾기 여부에 따라 parent 설정
        QMessageBox::information(this, "추가완료", "연락처가 추가되었습니다");

        // 디테일 페이지에서 디폴트 페이지로 전환
        ui->stackedWidget->setCurrentWidget(ui->defaultPage);
    });


}

void MainWindow::addNewContact()
{
    Contact *newContact = new Contact();
    newContact->name = ui->lineEdit_Name->text();
    newContact->phone= ui->lineEdit_Call->text();
    newContact->birthday = ui->dateEdit->date();
    newContact->location = ui->lineEdit_Location->text();
    newContact->favorite = ui->checkBox_Favorite->isChecked() ? 1 : 0;
    newContact->email= ui->lineEdit_Email->text();
    newContact->SNS = ui->lineEdit_SNS->text();
    newContact->memo = ui->textEdit_Memo->toPlainText();
    newContact->type = DataType::CONTACT;
    newContact->id = QUuid::createUuid().toString();

    Contact* parent = nullptr;
    if (newContact->favorite == 1) {
        parent = findFavoriteGroup();
    }
    if (!parent) {
        parent = model->getRoot(); // fallback
    }

    model->addContact(newContact, parent);
}

void MainWindow::clearDetailWindow()
{
    ui->lineEdit_Call->clear();
    ui->lineEdit_Name->clear();
    ui->lineEdit_Email->clear();
    ui->lineEdit_SNS->clear();
    ui->lineEdit_Location->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit_Memo->clear();
    ui->checkBox_Favorite->setCheckState(Qt::Unchecked);
}

void MainWindow::setDetailWindow(const QModelIndex &index)
{
    if (!index.isValid()) return;

    Contact* contact = static_cast<Contact*>(index.internalPointer());
    if (!contact) return;

    ui->lineEdit_Name->setText(contact->name);
    ui->lineEdit_Call->setText(contact->phone);
    ui->lineEdit_Email->setText(contact->email);
    ui->lineEdit_SNS->setText(contact->SNS);
    ui->lineEdit_Location->setText(contact->location); // 존재하는 경우
    ui->dateEdit->setDate(contact->birthday);
    ui->textEdit_Memo->setText(contact->memo);
    ui->checkBox_Favorite->setChecked(contact->favorite);
}

void MainWindow::slot_search()
{
        SearchDialog* dialog = new SearchDialog(model->getList(), this);

    connect(dialog, &SearchDialog::contactSelected, this, [=](Contact* contact){
        QModelIndex index = model->createIndexForNode(contact); // Contact*로 인덱스 생성
        if (index.isValid()) {
            currentSelected = index;
            setDetailWindow(index);
            ui->stackedWidget->setCurrentWidget(ui->detailPage);
        }
    });

    dialog->exec();
}


MainWindow::~MainWindow()
{}

Contact* MainWindow::findFavoriteGroup() {
    for (Contact* c : model->getRoot()->children) {
        if (c->name == "Favorite") {
            return c;
        }
    }
    return nullptr;
}
