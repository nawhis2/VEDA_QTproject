#include "SearchDialog.h"
#include "./ui_SearchDialog.h"


SearchDialog::SearchDialog(const QList<Contact*>& allContacts, QWidget* parent)
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

    //읽기 전용
    resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    resultView->resize(300, 200);
    resultView->move(80,100);
    resultView->verticalHeader()->setVisible(false);



    //-------------------------------------------------------------
    //검색 결과 더블클릭시 디테일 창 전환
    connect(resultView, &QTableView::doubleClicked, this, [=](const QModelIndex &index){

        if(!index.isValid()) return ;
        qDebug() << "bb1";
        // 더블클릭한 row의 0번째 컬럼에서 Contact* 꺼냄
        QStandardItem* item = resultModel->item(index.row(), 0);
        Contact* doubleClickedContact = static_cast<Contact*>(item->data().value<void*>());
                qDebug() << doubleClickedContact->name;
        if (!doubleClickedContact) {
            qDebug() << "포인터가 nullptr입니다.";
            return;
        }
        emit contactSelected(doubleClickedContact);
        this->accept();
    });

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
        for(const Contact* c: allContacts){
            if(c->name.contains(keyword, Qt::CaseInsensitive)){
                QList<QStandardItem*> row;

                QStandardItem* nameItem = new QStandardItem(c->name);
                nameItem->setData(QVariant::fromValue((void*)c));  // Contact* 저장!
                QStandardItem* phoneItem = new QStandardItem(c->phone);
                row << nameItem << phoneItem;

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
