#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "SearchDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    QString fullStyle = R"(
    QWidget {
        font-family: 'DungGeunMo';
        background-color: lavender;
        color: black;
        font-size: 14px;
    }

    QLineEdit, QDateEdit, QTextEdit {
        background-color: #ffffff;
        border: 1px solid #cccccc;
        border-radius: 5px;
        font-size: 12px;
        padding: 2px;
    }

    QPushButton {
        background-color: #b19cd9;
        color: black;
        border: none;
        font-size: 12px;
        padding: 6px 12px;
        border-radius: 8px;
    }

    QPushButton:hover {
        background-color: #a58ed6;
    }

    QPushButton:pressed {
        background-color: #9370db;
    }

    QTreeView {
        background-color: #f5f0ff;
        border: 1px solid #d0c4e8;
    }

    QHeaderView::section {
        background-color: #d6c6f0;
        color: black;
        padding: 4px;
        border: none;
    }
)";

    int id = QFontDatabase::addApplicationFont(":resources/DungGeunMo.ttf");

    if (id != -1) {
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont customFont(family);
        customFont.setPointSize(12);  // 글자 크기 설정
        qApp->setFont(customFont);    // 앱 전체에 적용
    } else
    {
        qDebug() << "폰트 로드 실패!";
    }
    qDebug() << "로드된 폰트 수:" << QFontDatabase::applicationFontFamilies(id).size();
    qDebug() << "폰트 이름:" << QFontDatabase::applicationFontFamilies(id);


    ui->setupUi(this);
    this->setStyleSheet(fullStyle);

    QPixmap insta(":resources/Link.png");
    ui->pushButton_SNS->setIcon(QIcon(insta));

    QPixmap plus(":resources/UserPlus.png");
    ui->pushButton_Add->setIcon(QIcon(plus));

    QPixmap minus(":resources/UserX.png");
    ui->pushButton_Delete->setIcon(QIcon(minus));

    QPixmap savef(":resources/SaveFile.png");
    ui->pushButton_SaveFile->setIcon(QIcon(savef));

    QPixmap loadf(":resources/LoadFile.png");
    ui->pushButton_LoadFile->setIcon(QIcon(loadf));

    QPixmap search(":resources/Search.png");
    ui->pushButton_Search->setIcon(QIcon(search));

    QPixmap Goback(":resources/Back.png");
    ui->pushButton_Goback->setIcon(QIcon(Goback));

    QPixmap Exit(":resources/off.png");
    ui->pushButton_Exit->setIcon(QIcon(Exit));

    ui->checkBox_Favorite->setStyleSheet(R"(
    QCheckBox::indicator {
        width: 20px;
        height: 20px;
    }
    QCheckBox::indicator:unchecked {
        image: url(:/resources/starOff.png);
    }
    QCheckBox::indicator:checked {
        image: url(:/resources/starOn.png);
    }
)");
    ui->treeView_PhoneBook->setStyleSheet(R"(
    QTreeView::item {
        padding-top: 8px;
        padding-bottom: 8px;
    }
)");


    //-----------------------------------------------------------------------

    ui->dateEdit->setDate(QDate::currentDate());
    model = new ContactModel(this);

    ui->treeView_PhoneBook->setModel(model);
    ui->treeView_PhoneBook->setHeaderHidden(false); // 헤더 보이기

    connect(ui->pushButton_Search, &QPushButton::clicked, this, &MainWindow::slot_search);
    connect(ui->pushButton_SaveFile, &QPushButton::clicked, this, &MainWindow::saveToJson);
    connect(ui->pushButton_LoadFile, &QPushButton::clicked, this, &MainWindow::loadToJson);
    connect(ui->pushButton_Exit, &QPushButton::clicked, qApp, &QApplication::exit);
    connect(ui->pushButton_Add, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->detailPage);
        currentDetailData = QModelIndex();
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
        qDebug() << contact ;
        if (contact == nullptr)
        {
            QMessageBox::warning(this, "Warning", "문제가 발생하였습니다.");
            return;
        }
        model->removeContact(contact);

        currentSelected = QModelIndex(); // 선택 초기화
    });

    connect(ui->treeView_PhoneBook, &QTreeView::doubleClicked, this, [=](const QModelIndex &index){
        Contact* contact = static_cast<Contact*>(index.internalPointer());
        if (!contact || contact->type == DataType::GROUP) return;

        currentDetailData = index;
        ui->stackedWidget->setCurrentWidget(ui->detailPage);

        setDetailWindow(index);
    });


    // ---  window 2  ---
    ui->lineEdit_Name->setMaxLength(20); // 20자까지만 입력 허용
    QIntValidator* validator = new QIntValidator(0, 99999999999, this);  // 최대 11자리 숫자
    ui->lineEdit_Call->setValidator(validator);
    // ui->lineEdit_Call->setMaxLength(20); // 20자까지만 입력 허용
    ui->lineEdit_Email->setMaxLength(30); // 20자까지만 입력 허용
    ui->lineEdit_Location->setMaxLength(50); // 20자까지만 입력 허용
    ui->lineEdit_SNS->setMaxLength(20); // 20자까지만 입력 허용

    ui->lineEdit_Email->setPlaceholderText("example@email.com");
    ui->lineEdit_Call->setPlaceholderText("숫자만 입력하세요...");
    ui->lineEdit_Name->setPlaceholderText("이름을 입력하세요...");
    ui->lineEdit_Location->setPlaceholderText("주소를 입력하세요...");
    ui->lineEdit_SNS->setPlaceholderText("@_______");


    connect(ui->pushButton_Goback, &QPushButton::clicked, this, [&](){
        ui->stackedWidget->setCurrentWidget(ui->defaultPage);
    });

    connect(ui->pushButton_Save, &QPushButton::clicked, this, [&](){
        if (ui->lineEdit_Name->text() == "")
        {
            QMessageBox::warning(this, "Error", "이름을 입력하세요");
            return ;
        }

        if (currentDetailData == QModelIndex())
        {
            addNewContact();
            clearDetailWindow();

            // 즐겨찾기 여부에 따라 parent 설정
            QMessageBox::information(this, "추가완료", "연락처가 추가되었습니다");
            // 디테일 페이지에서 디폴트 페이지로 전환
            ui->stackedWidget->setCurrentWidget(ui->defaultPage);
        }
        else
        {
            Contact *contact = static_cast<Contact*>(currentDetailData.internalPointer());
            qDebug() << contact;
            bool isToggled = (contact->favorite != ui->checkBox_Favorite->checkState()) ? 1 : 0;
            editContact(contact);
            qDebug() << "toggle : " << isToggled;
            if (isToggled)
                model->toggleFavorite(contact);
            setDetailWindow(currentDetailData);
            QMessageBox::information(this, "변경완료", "연락처가 변경되었습니다");
        }
    });

    connect(ui->pushButton_SNS, &QPushButton::clicked, this, [&](){
        QDesktopServices::openUrl(QUrl("https://instagram.com/" + ui->lineEdit_SNS->text()));
    });
}

void MainWindow::addNewContact()
{
    Contact *newContact = new Contact();
    qDebug() << "add 1" << currentDetailData;

    editContact(newContact);

    qDebug() << "add 2" << currentDetailData;

    Contact* parent = nullptr;
    if (newContact->favorite == 1) {
        parent = findFavoriteGroup();
    }
    if (!parent) {
        parent = model->getRoot(); // fallback
    }

    model->addContact(newContact, parent);
}

void MainWindow::editContact(Contact *contact)
{
    contact->name = ui->lineEdit_Name->text();
    contact->phone= ui->lineEdit_Call->text();
    contact->birthday = ui->dateEdit->date();
    contact->location = ui->lineEdit_Location->text();
    contact->favorite = ui->checkBox_Favorite->isChecked() ? 1 : 0;
    contact->email= ui->lineEdit_Email->text();
    contact->SNS = ui->lineEdit_SNS->text();
    contact->memo = ui->textEdit_Memo->toPlainText();
    contact->type = DataType::CONTACT;
    contact->id = QUuid::createUuid().toString();
    // qDebug() << "Toggling complete";

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

//-----------------------------------------------------------

Contact* MainWindow::findFavoriteGroup() {
    for (const auto& c : model->getRoot()->children) {
        if (c->name == "Favorite" && c->type == DataType::GROUP) {
            return c;
        }
    }
    return nullptr;
}

//-----------------------------------------------------------
//Json 파일 저장하기
void MainWindow::saveToJson()
{
    QJsonArray array;

    QString path = QFileDialog::getSaveFileName(this, "연락처_파일_저장");
    QList<Contact*> allContacts = model->getList();
    for (Contact* c : allContacts) {
        QJsonObject obj;
        obj["name"] = c->name;
        obj["phone"] = c->phone;
        obj["email"] = c->email;
        obj["favorite"] = c->favorite;
        obj["birthday"] = c->birthday.toString(Qt::ISODate);
        obj["SNS"] = c->SNS;
        obj["location"] = c->location;
        obj["memo"] = c->memo;

        if (c->type == DataType::GROUP)
            obj["type"] = 0;
        else
            obj["type"] = 1;

        array.append(obj);
    }

    QJsonDocument doc(array);
    QFile file(path); // path
    if (!file.open(QIODevice::WriteOnly)) { //쓰기 모드로 열기
        QMessageBox::warning(this, "오류", "파일을 저장할 수 없습니다");
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); //JSON 텍스트로 쓰기
    file.close();

    QMessageBox::information(this, "저장 완료", "연락처를 저장했습니다");
}


//----------------------------------------------------
//Json 파일 불러오기
void MainWindow::loadToJson()
{
    model->clearAll();
    QString path = QFileDialog::getOpenFileName(this, "연락처_파일_불러오기");
        // getSaveFileName(this, "연락처_파일_저장");
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::warning(this, "오류", "파일을 불러올 수 없습니다");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);

    QJsonArray array = doc.array();
    for (const QJsonValue &val : array) {
        QJsonObject obj = val.toObject();

        Contact* c = new Contact();
        c->name = obj["name"].toString();
        c->phone = obj["phone"].toString();
        c->email = obj["email"].toString();
        c->favorite = obj["favorite"].toBool();

        if (obj["type"].toInt() == 0)
            c->type = DataType::GROUP;
        else
            c->type = DataType::CONTACT;

        c->birthday.toString(Qt::ISODate) = obj["birthday"].toString();
        c->SNS = obj["SNS"].toString();
        c->location = obj["location"].toString();
        c->memo = obj["memo"].toString();

        if (c->favorite)
            model->addContact(c, model->getFavorite());
        else
            model->addContact(c, model->getRoot());
    }

    QMessageBox::information(this, "불러오기 완료", "연락처를 불러왔습니다");
}

