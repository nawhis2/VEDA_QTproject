#include "WeatherManager.h"

WeatherManager::WeatherManager(QObject* mainwindow)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [&](QNetworkReply* reply) {
        QByteArray response = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(response);
        if (doc.object().contains("error") && doc.object()["error"].toBool())
        {
            QMessageBox::warning(nullptr, "Error", "날씨 수신에 실패했습니다.");
            emit dataReceived("");

            return;
        }

        QJsonObject obj = doc.object()["current_weather"].toObject();
        int weatherCode = obj["weathercode"].toInt();
        QString weatherText = weatherCodeToText(weatherCode);
        emit dataReceived(weatherText);
    });

    QString url = "https://api.open-meteo.com/v1/forecast?latitude=37.5665&longitude=126.9780&current_weather=true";
    manager->get(QNetworkRequest(QUrl(url)));
}

WeatherManager::~WeatherManager()
{
    delete manager;
}

QString WeatherManager::weatherCodeToText(int code)
{
    switch (code)
    {
    case 0:  return "🌞";
    case 1:  return "🌤";
    case 2:  return "⛅";
    case 3:  return "☁";
    case 45: // 안개
    case 48: return "🌫";
    case 51: case 53: case 55:
    case 56: case 57:
    case 61: case 63: case 65:
    case 66: case 67:
        return "☂";
    case 71: case 73: case 75:
    case 77:
        return "❄";
    case 80: case 81: case 82:
        return "🌦";
    case 85: case 86:
        return "❄";
    case 95:
    case 96: case 99:
        return "⚡";
    default:
        return "알 수 없는 날씨";
    }
}