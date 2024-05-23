// LoginWindow.h
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QFile> // Добавляем заголовочный файл QFile

class LoginWindow : public QWidget {
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void onLoginButtonClicked();

private:
    // Здесь можно добавить элементы управления, такие как поля ввода логина и пароля
    QFile file; // Добавляем объект QFile для открытия файла .ui
};

#endif // LOGINWINDOW_H
