#include "mainwindow.h"
#include "newloginwindow.h"
#include "tests/testdatabase.hpp"
#include "tests/testnewloginwindow.hpp"
#include "tests/testmainwindow.hpp"

#include <iostream>
#include <QApplication>
#include <QLocale>
#include <QTest>


void conductTesting(int argc, char *argv[])
{
    QTest::qExec(new TestDatabase, argc, argv);       // Database
    QTest::qExec(new TestNewLoginWindow, argc, argv); // NewLoginWindow
    QTest::qExec(new TestMainWindow, argc, argv);     // MainWindow
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    conductTesting(argc, argv); // TESTS

    NewLoginWindow loginWindow;
    try
    {
        loginWindow.show();
    }
    catch (const std::exception& e)
    {
        std::cout << "Caught exception in showing loginwindow: " << e.what() << std::endl;
    }
    return a.exec();
}
