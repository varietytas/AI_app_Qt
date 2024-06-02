#ifndef TESTNEWLOGINWINDOW_HPP
#define TESTNEWLOGINWINDOW_HPP

#include "../newloginwindow.h"
#include "../ui_newloginwindow.h"
#include "../mainwindow.h"
#include <QObject>
#include <QTest>


class TestNewLoginWindow : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();    // Initializes the unit test
    void cleanupTestCase(); // Cleans up after all tests are done

    void testLoginButton();     // Fills in the fields and tests "Login" button behaviour
    void testRegisterButton();  // Fills in the fields and tests "Register" button behaviour

private:
    NewLoginWindow* loginWindow;
};

#endif // TESTNEWLOGINWINDOW_HPP
