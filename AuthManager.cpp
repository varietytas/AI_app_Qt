// AuthManager.cpp
#include "AuthManager.h"

AuthManager::AuthManager(QObject *parent) : QObject(parent), settings("YourCompany", "YourApp") {}

bool AuthManager::isLogin() const {
    return false;
    return settings.value("authenticated", false).toBool();
}

void AuthManager::setAuthenticated(bool authenticated) {
    settings.setValue("authenticated", authenticated);
}
