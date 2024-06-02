#include "requestsToBackend.h"
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>
#include "log.h"

// Функция для преобразования QString в std::string
std::string QStringToStdString(const QString& qStr) {
    QByteArray byteArray = qStr.toUtf8();
    return std::string(byteArray.constData(), byteArray.length());
}

// Конструктор класса AuthUser
AuthUser::AuthUser(QString email, QString password, QString token)
        : email(email), password(password), token(token) {}

// Создание экземпляра класса Logger
Logger logger("../log.txt");

QString AuthUser::get_code(QString tg_id) {
    logger.writeToLog("AuthUser::get_code called with tg_id: " + tg_id);
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;
    json_obj["tg_id"] = tg_id;
    QJsonObject response_json = send_request(json_obj, "http://62.113.113.54:5000/email", "POST");
    QString message = response_json["message"].toString();
    logger.writeToLog("AuthUser::get_code response message: " + message);
    return message;
}

void AuthUser::sendPost(QString message) {
    logger.writeToLog("AuthUser::sendPost called with message: " + message);
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;
    json_obj["message"] = message;
    QJsonObject response_json = send_request(json_obj, "http://62.113.113.54:5000/send_message", "POST");
    logger.writeToLog("AuthUser::sendPost response: " + QJsonDocument(response_json).toJson());
}

QString AuthUser::get_post_text(const QString& request) {
    logger.writeToLog("AuthUser::get_post_text called with request: " + request);
    QJsonObject json_obj;
    json_obj["token"] = this->token;
    json_obj["question"] = request;
    QJsonObject response_json = send_request(json_obj, "http://62.113.113.54:5000/yandexgpt", "POST");
    QString text = response_json["message"].toString();
    logger.writeToLog("AuthUser::get_post_text response text: " + text);
    return text;
}

bool AuthUser::checkIfUserExists() {
    logger.writeToLog("AuthUser::checkIfUserExists called");
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;
    QJsonObject response_json = send_request(json_obj, "http://62.113.113.54:5000/check_email", "POST");
    QString response_message = response_json["message"].toString();
    std::string message = QStringToStdString(response_message);
    logger.writeToLog("AuthUser::checkIfUserExists response message: " + response_message);
    if (message == "Yes") {
        return true;
    }
    return false;
}

QJsonObject AuthUser::send_request(const QJsonObject& json_obj, const QString& url, const QString& method) {
    logger.writeToLog("AuthUser::send_request called with URL: " + url + " and method: " + method);
    logger.writeToLog("Request JSON: " + QJsonDocument(json_obj).toJson());

    QUrl url1 = QUrl(url);
    QNetworkRequest request(url1);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkAccessManager networkManager;
    QJsonDocument doc(json_obj);
    QByteArray data = doc.toJson();

    QNetworkReply* reply = nullptr;
    if (method.toUpper() == "POST") {
        reply = networkManager.post(request, data);
    } else {
        reply = networkManager.get(request);  // Simplified, for demonstration purposes
    }

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        logger.writeToLog("Network error: " + reply->errorString());
        reply->deleteLater();
        return QJsonObject();  // Return an empty JSON object on error
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument response_doc = QJsonDocument::fromJson(response_data);
    QJsonObject response_json = response_doc.object();

    logger.writeToLog("AuthUser::send_request response JSON: " + response_doc.toJson());

    reply->deleteLater();

    return response_json;
}
