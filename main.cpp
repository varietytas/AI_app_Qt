#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "NewLoginWindow.h"
#include "requestsToBackend.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
//    NewLoginWindow loginWindow;
//    loginWindow.show();

//    return a.exec();
}

