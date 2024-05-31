#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "NewLoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NewLoginWindow loginWindow;
    loginWindow.show();
    return a.exec();
}
