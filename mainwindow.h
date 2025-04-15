#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDateEdit>
#include <QList>
#include <QTableView>
#include <QTreeView>
#include <QDate>
#include <QDateEdit>
#include "Contact.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    ContactModel*   model;
    QTreeView*      treeView;
    QModelIndex     currentSelected;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addNewContact();
    void clearDetailWindow();
    void setDetailWindow(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Contact* findFavoriteGroup();

public slots:
    // void slot_add();
    void slot_search();
};
#endif // MAINWINDOW_H
