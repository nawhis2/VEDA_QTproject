#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class SearchDialog;
}
QT_END_NAMESPACE

struct Contact;

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    SearchDialog(const QList<Contact>& allContacts, QWidget* parent = nullptr);

signals:
    void contactSelected(const QString &name);

private slots:
    void performSearch(const QString& keyword);

private:
    Ui::SearchDialog *uis;

    QComboBox* filterComboBox;
    QLineEdit*  keywordLineEdit;
    QPushButton*    searchButton;
    QTableView* resultView;
    QStandardItemModel* resultModel;
    QList<Contact> allContacts;

};

#endif // SEARCHDIALOG_H
