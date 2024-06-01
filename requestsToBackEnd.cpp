#include "requestsToBackend.h"
#include <QNetworkAccessManager>
#include <string>
#include <QString>
std::string QStringToStdString(const QString& qStr) {
    QByteArray byteArray = qStr.toUtf8();
    return std::string(byteArray.constData(), byteArray.length());
}

AuthUser::AuthUser(QString email, QString password, QString token)
        : email(email), password(password), token(token) {}

QString AuthUser::get_code(QString tg_id) {
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;
    json_obj["tg_id"] = tg_id;
    QJsonObject response_json = send_request(json_obj, "http://127.0.0.1:5000/email", "POST");
    QString message = response_json["message"].toString();
    return message;
//    return response_json;
}

QString AuthUser::get_post_text(const QString& request) {
    QJsonObject json_obj;
    json_obj["token"] = this->token;
    json_obj["question"] = request;

    QJsonObject response_json = send_request(json_obj, "http://127.0.0.1:5000/yandexgpt", "POST");
    QString text = response_json["message"].toString();

    return text;
}

bool AuthUser::checkIfUserExists(){
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;
    QJsonObject response_json = send_request(json_obj, "http://127.0.0.1:5000/check_email", "POST");
    QString response_message = response_json["message"].toString();
    std::string message = QStringToStdString(response_message);
    if (message=="Yes"){
        return true;
    }
    return false;
}





QJsonObject AuthUser::send_request(const QJsonObject& json_obj, const QString& url, const QString& method) {
    QUrl url1 = QUrl(url);
    QNetworkRequest request(url1);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");

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
        qWarning() << "Network error: " << reply->errorString();
        reply->deleteLater();
        return QJsonObject();  // Return an empty JSON object on error
    }

    QByteArray response_data = reply->readAll();
    QJsonDocument response_doc = QJsonDocument::fromJson(response_data);
    QJsonObject response_json = response_doc.object();

    reply->deleteLater();

    return response_json;
}



