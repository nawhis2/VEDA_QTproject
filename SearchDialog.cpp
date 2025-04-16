#include "SearchDialog.h"
#include "./ui_SearchDialog.h"

SearchDialog::SearchDialog(const QList<Contact*>& allContacts, QWidget* parent)
    : QDialog(parent)
    , uis(new Ui::SearchDialog)
{
    uis->setupUi(this);

    uis->lineEdit->setPlaceholderText("찾을 이름을 입력해주세요...");

    SetModelView();
    SettableUi();

    connect(uis->tableView, &QTableView::doubleClicked, this, [=](const QModelIndex &index){
        if(!index.isValid()) return ;

        QStandardItem* item = resultModel->item(index.row(), 0);
        Contact* doubleClickedContact = static_cast<Contact*>(item->data().value<void*>());
        if (!doubleClickedContact) {
            return;
        }
        emit contactSelected(doubleClickedContact);
        this->accept();
    });

    connect(uis->pushButton, &QPushButton::clicked, this, [=](){

        QString keyword = uis->lineEdit->text();
        resultModel->clear();
        resultModel->setHorizontalHeaderLabels({"이름", "전화번호"});

        if (keyword == "") {
            SettableUi();
            QMessageBox::warning(this, "Error", "이름을 입력해주세요.");
            return;
        }

        int count = 0;
        for(const Contact* c: allContacts){
            if(c->name.contains(keyword, Qt::CaseInsensitive)){
                QList<QStandardItem*> row;

                QStandardItem* nameItem = new QStandardItem(c->name);
                nameItem->setData(QVariant::fromValue((void*)c));
                QStandardItem* phoneItem = new QStandardItem(c->phone);
                row << nameItem << phoneItem;

                resultModel->appendRow(row);
                count++;
                SettableUi();
            }
        }

        if (count == 0) {
            SettableUi();
            QMessageBox::warning(this, "Error", "검색 결과가 없습니다.");
            return;
        }
    });
}

void SearchDialog::SettableUi()
{
    uis->tableView->setColumnWidth(0, 120);
    uis->tableView->setColumnWidth(1, 230);

    uis->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    uis->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
}

void SearchDialog::SetModelView()
{
    resultModel = new QStandardItemModel();
    resultModel->setHorizontalHeaderLabels({"이름", "전화번호"});
    uis->tableView->setModel(resultModel);
    uis->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    uis->tableView->verticalHeader()->setVisible(false);
}
