#include "SearchDialog.h"
#include "./ui_SearchDialog.h"


SearchDialog::SearchDialog(const QList<Contact>& allContacts, QWidget* parent)
    : QDialog(parent)
    , uis(new Ui::SearchDialog)
{
    uis->setupUi(this);


    //-------------------------------------------------------------
    //헤더 표시
    resultModel = new QStandardItemModel();
    resultModel->setHorizontalHeaderLabels({"이름", "전화번호"});

    resultView = new QTableView(this);
    resultView->setModel(resultModel);

    resultView->resize(300, 200);
    resultView->move(80,100);


    //-------------------------------------------------------------
    //검색 푸시버튼 눌렀을 경우 -> 키워드에 맞는 정보 불러오기
    //QStandardItemModel::appendRow() 함수는 QList<QStandardItem*> 타입을 필수로 요구


    connect(uis->pushButton, &QPushButton::clicked, this, [=](){

        QString keyword = uis->lineEdit->text();
        resultModel->clear();
        resultModel->setHorizontalHeaderLabels({"이름", "전화번호"});

        //키워드 입력 안했을 경우, 메세지 박스
        if (keyword == "") {
            QMessageBox::warning(this, "", "이름을 입력해주세요.");
            return;
        }


        int count = 0;
        for(const Contact& c: allContacts){
            if(c.name.contains(keyword, Qt::CaseInsensitive)){
                QList<QStandardItem*> row;
                row << new QStandardItem(c.name);
                row << new QStandardItem(c.phone);
                resultModel->appendRow(row);
                count++;
            }
        }

        //키워드 검색 결과 없을 경우, 메세지 박스
        if (count == 0) {
            QMessageBox::warning(this, "", "검색 결과가 없습니다.");
            return;
        }
    });

}

void SearchDialog::performSearch(const QString& keyword)
{}
