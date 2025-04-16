#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QByteArray>
// #include "mainwindow.h"

class WeatherManager : public QObject
{
    QNetworkAccessManager*  manager;
    QString weatherCodeToText(int code);
    QString                 weatherData;

public:
    explicit WeatherManager(QObject*);
    ~WeatherManager();
    QString                 getWeatherData();
};

#endif // WEATHERMANAGER_H
