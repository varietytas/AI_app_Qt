// LoginWindow.cpp
#include "LoginWindow.h"
#include "AuthManager.h"
#include <QPushButton>
#include <QVBoxLayout>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *loginButton = new QPushButton("Login", this);

    layout->addWidget(loginButton);
    setLayout(layout);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
}

void LoginWindow::onLoginButtonClicked() {
    // Здесь можно добавить логику проверки логина и пароля

    // Если аутентификация успешна:
    AuthManager authManager;
    authManager.setAuthenticated(true);

    emit loginSuccessful();
}

