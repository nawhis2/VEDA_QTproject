#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include <QHeaderView>

QT_BEGIN_NAMESPACE
namespace Ui {
class SearchDialog;
}
QT_END_NAMESPACE

class SearchDialog : public QDialog
{
    Q_OBJECT

    Ui::SearchDialog *uis;

    QTableView* resultView;
    QStandardItemModel* resultModel;
    QList<Contact*> allContacts;

private:
    void SettableUi();
    void SetModelView();

public:
    SearchDialog(const QList<Contact*>& allContacts, QWidget* parent = nullptr);

signals:
    void contactSelected(Contact* contact);
};

#endif // SEARCHDIALOG_H
