#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QByteArray>
#include <QMessageBox>
// #include "mainwindow.h"

class WeatherManager : public QObject
{
    Q_OBJECT

    QNetworkAccessManager*  manager;
    QString weatherCodeToText(int code);
    QString                 weatherData;

public:
    explicit WeatherManager(QObject*);
    ~WeatherManager();

signals:
    void dataReceived(QString weather);
};

#endif // WEATHERMANAGER_H
