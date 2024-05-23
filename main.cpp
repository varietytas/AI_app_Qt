#include "mainwindow.h"
// #include <boost/json.hpp>
// #include "requestsToBackend.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "database.h"
#include "LoginWindow.h"
#include "mainwindow.h"
#include "AuthManager.h"
// namespace json = boost::json;       // from <boost/json.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // AuthManager authManager;
    /*if (!authManager.isLogin()) {
        LoginWindow loginWindow;
        loginWindow.show();

        // Подключаем сигнал успешного входа к открытию главного окна
        QObject::connect(&loginWindow, &LoginWindow::loginSuccessful, [&]() {
            MainWindow mainWindow;
            mainWindow.show();
            loginWindow.close(); // Закрываем окно входа после успешного входа
        });

        // Запускаем цикл обработки событий приложения
        return a.exec();
    } else {
        // Если пользователь уже авторизован, отображаем главное окно сразу
        MainWindow mainWindow;
        mainWindow.show();
        return a.exec();
    }*/

    // json::value json_obj;
    // std::string url;
    // json::value answer;

    // json_obj = json::parse(R"({ "name": "John", "age": 30, "car": null })");
    // answer = send_request(json_obj,url,"GET");
    // std::cout << answer << std::endl;
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ai-qt-app_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    // Maximize window on startup
    // w.setWindowState(Qt::WindowMaximized);
    // Database db;

    // db.createTables();
    // db.addText("firstname", "2", "3",   "5");
    // db.addText("firstname23", "2", "3",   "5");
    // db.addText("firstnamewe321", "2", "3",   "5");
    // db.addText("firstname34323", "2", "3",   "5");
    // db.addText("firstname3432", "2", "3",   "5");
    // for (UserInfo t: db.getAllTexts())
    // {
    //     std::cout << t.id << '\t' << t.firstname << '\n';
    // }
    w.show();
    return a.exec();
}
