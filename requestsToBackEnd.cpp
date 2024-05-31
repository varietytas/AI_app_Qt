#include "requestsToBackend.h"
#include <QNetworkAccessManager>
AuthUser::AuthUser(QString email, QString password, QString token)
        : email(email), password(password), token(token) {}

QJsonObject AuthUser::get_token() {
    QJsonObject json_obj;
    json_obj["email"] = this->email;
    json_obj["password"] = this->password;

    QJsonObject response_json = send_request(json_obj, apiUrl + "/login", "POST");
    if (response_json.contains("token")) {
        this->token = response_json["token"].toString();
    }

    return response_json;
}

QJsonObject AuthUser::get_post_text(const QString& request) {
    QJsonObject json_obj;
    json_obj["token"] = this->token;
    json_obj["request"] = request;

    QJsonObject response_json = send_request(json_obj, apiUrl + "/text_request", "POST");
    if (response_json.contains("token")) {
        this->token = response_json["token"].toString();
    }

    return response_json;
}

QJsonObject AuthUser::send_request(const QJsonObject& json_obj, const QString& url, const QString& method) {
    QUrl url1 = QUrl(url);
    QNetworkRequest request(url1);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

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