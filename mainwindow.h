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
#include <QDesktopServices>
#include "Contact.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QLabel>

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
    QModelIndex     currentDetailData;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addNewContact();
    void clearDetailWindow();
    void setDetailWindow(const QModelIndex &index);
    void editContact(Contact *contact);
    void saveToJson();
    void loadToJson();
    void startBannerAnimation();

    void updateBirthdayLabel();

private:
    Ui::MainWindow *ui;
    Contact* findFavoriteGroup();
    QLabel* bannerLabel;
    QPropertyAnimation *bannerAnimation;

public slots:
    // void slot_add();
    void slot_search();
};
#endif // MAINWINDOW_H
