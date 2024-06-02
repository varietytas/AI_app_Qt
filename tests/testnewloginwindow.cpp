#include "testnewloginwindow.hpp"

void TestNewLoginWindow::initTestCase()
{
    loginWindow = new NewLoginWindow();
    loginWindow->show();
}
void TestNewLoginWindow::cleanupTestCase() { delete loginWindow; }

void TestNewLoginWindow::testLoginButton()
{
    // Set email and password fields
    QLineEdit* emailField = loginWindow->findChild<QLineEdit*>("lineEditEmail");
    QLineEdit* passwordField = loginWindow->findChild<QLineEdit*>("lineEditPassword");
    QPushButton* loginButton = loginWindow->findChild<QPushButton*>("pushButtonLogin");

    QVERIFY(emailField);
    QVERIFY(passwordField);
    QVERIFY(loginButton);

    // Fill in
    emailField->setText("test@example.com");
    passwordField->setText("password123");

    QTest::mouseClick(loginButton, Qt::LeftButton);

    // Check if MainWindow is set as the central widget
    QWidget* centralWidget = loginWindow->centralWidget();
    QVERIFY(dynamic_cast<MainWindow*>(centralWidget) != nullptr);
}

void TestNewLoginWindow::testRegisterButton()
{
    // Set registration fields
    QLineEdit* nameField = loginWindow->findChild<QLineEdit*>("lineEditname");
    QLineEdit* emailRegField = loginWindow->findChild<QLineEdit*>("lineEditemailreg");
    QLineEdit* passwordRegField = loginWindow->findChild<QLineEdit*>("lineEditPassword_1");
    QLineEdit* channelField = loginWindow->findChild<QLineEdit*>("lineEditchannel");
    QPushButton* registerButton = loginWindow->findChild<QPushButton*>("pushButtonRegister");

    QVERIFY(nameField);
    QVERIFY(emailRegField);
    QVERIFY(passwordRegField);
    QVERIFY(channelField);
    QVERIFY(registerButton);

    // Fill in
    nameField->setText("Test User");
    emailRegField->setText("test@example.com");
    passwordRegField->setText("password123");
    channelField->setText("Test Channel");

    QTest::mouseClick(registerButton, Qt::LeftButton);

    // Check if MainWindow is set as the central widget
    QWidget* centralWidget = loginWindow->centralWidget();
    QVERIFY(dynamic_cast<MainWindow*>(centralWidget) != nullptr);
}
