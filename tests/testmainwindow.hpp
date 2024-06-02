#ifndef TESTMAINWINDOW_HPP
#define TESTMAINWINDOW_HPP

#include "../mainwindow.h"
#include "../ui_mainwindow.h"
#include <QObject>
#include <QTest>


class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();    // Initializes the unit test
    void cleanupTestCase(); // Cleans up after all tests are done

    void testInitialUIState();
    void testGenerateButton();
    void testResetButton();
    void testDoneButton();
    // void testCMSButton();

private:
    MainWindow* mainWindow;
};

#endif // TESTMAINWINDOW_HPP
