// AuthManager.h
#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QSettings>

class AuthManager : public QObject {
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

    bool isLogin() const;
    void setAuthenticated(bool authenticated);

private:
    QSettings settings;
};

#endif // AUTHMANAGER_H
