
#ifndef REQUESTSTOBACKEND_H
#define REQUESTSTOBACKEND_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QEventLoop>
class AuthUser {

public:
    QString email;
    QString password;  // In md5 hash
    QString token;


    AuthUser(QString email, QString password, QString token);

    QJsonObject get_token();
    QJsonObject get_post_text(const QString& request);

private:
    QString apiUrl= "http://localhost:8000";
    QJsonObject send_request(const QJsonObject& json_obj, const QString& url, const QString& method);
};
#endif
