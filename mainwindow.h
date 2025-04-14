#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDateEdit>
#include <QList>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct Contact
{
    int         id;
    QString     name;
    QString     phone;
    QDate       birthday;
    QString     email;
    QString     SNS; // insta
    QString     Memo;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QList<Contact> allContacts;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


public slots:
    // void slot_add();
    void slot_search();
};
#endif // MAINWINDOW_H
