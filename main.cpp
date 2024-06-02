#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <iostream>
#include <QTranslator>
#include "requestsToBackend.h"
#include "newloginwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    NewLoginWindow loginWindow;
    try
    {
        loginWindow.show();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception in showing loginwindow: " << e.what() << std::endl;
    }
    return a.exec();
}
