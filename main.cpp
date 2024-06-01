#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "NewLoginWindow.h"
#include "requestsToBackend.h"
<<<<<<< HEAD
=======
#include "newloginwindow.h"
>>>>>>> a12d029292973d779f48dea014be0144b2933749

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow window;
//    window.show();
//    return a.exec();
    NewLoginWindow loginWindow;
    loginWindow.show();

    return a.exec();
}

