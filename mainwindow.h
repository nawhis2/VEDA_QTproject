#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateEdit>
#include <QTreeView>
#include <QDesktopServices>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QByteArray>
#include <QNetworkReply>
#include "Contact.h"
#include "WeatherManager.h"

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
    WeatherManager* weatherManager;

    Ui::MainWindow *ui;
    QLabel* bannerLabel;
    QPropertyAnimation *bannerAnimation;

private:
    void setSystemStyle();
    void setLineEditProperty();
    void setBannerProperty();

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

public slots:
    void slot_search();
};
#endif // MAINWINDOW_H
