#include "mainwindow.h"
// #include <boost/json.hpp>
// #include "requestsToBackend.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
// namespace json = boost::json;       // from <boost/json.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
    w.show();
    return a.exec();
}
