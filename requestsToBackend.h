
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
    void sendPost(QString message);
    QString get_code(QString tg_id);
    QString get_post_text(const QString& request);
    bool checkIfUserExists();

    QString make_strapi_post(const QString& request);
    QJsonArray get_strapi_posts();
    QJsonObject get_token();
  
private:
    QString apiUrl= "http://62.113.113.54:8000";
    QJsonObject send_request(const QJsonObject& json_obj, const QString& url, const QString& method);

    
};
#endif
