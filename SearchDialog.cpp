#include "SearchDialog.h"
#include "./ui_SearchDialog.h"


SearchDialog::SearchDialog(const QList<Contact>& allContacts, QWidget* parent)
    : QDialog(parent)
    , uis(new Ui::SearchDialog)
{
    // this->show();
    uis->setupUi(this);

    // resultModel = new QStandardItemModel();
    // resultModel->setHorizontalHeaderLabels({"이름", "전화번호"});

    // QList<QStandardItem*> row;
    // row << new QStandardItem("영서") << new QStandardItem("010-1234-1234");
    // resultModel->appendRow(row);

    // resultView = new QTableView(this);
    // resultView->setModel(resultModel);

    // resultView->resize(300, 400);
    // resultView->move(100,100);


    // for(const Contact& c: allContacts){
    //     if(c.name.contains("영서", Qt::CaseInsensitive)){
    //         QList<QStandardItem*> row; //한 줄을 구성할 셀 리스트
    //         row << QStandardItem(c.name);
    //         row << QStandardItem(c.phone);
    //         headers->appendRow(row);
    //     }
    // }
}

void SearchDialog::performSearch(const QString& keyword)
{}
