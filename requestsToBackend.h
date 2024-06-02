#ifndef REQUESTSTOBACKEND_H
#define REQUESTSTOBACKEND_H

#include <QString>
#include <QJsonObject>

// Declaration of customMessageHandler
//void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
std::string QStringToStdString(const QString& qStr);

class AuthUser {
public:
    AuthUser(QString email, QString password, QString token);
    QString get_code(QString tg_id);
    void sendPost(QString message);
    QString get_post_text(const QString& request);
    bool checkIfUserExists();

private:
    QString email;
    QString password;
    QString token;

    QJsonObject send_request(const QJsonObject& json_obj, const QString& url, const QString& method);
};

#endif // REQUESTSTOBACKEND_H
