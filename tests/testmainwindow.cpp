#include "testmainwindow.hpp"

void TestMainWindow::initTestCase()
{
    mainWindow = new MainWindow();
    mainWindow->show();
}
void TestMainWindow::cleanupTestCase() { delete mainWindow; }

// Ensures the initial state of the UI elements is as expected (empty text fields).
void TestMainWindow::testInitialUIState()
{
    QPlainTextEdit* queryField = mainWindow->findChild<QPlainTextEdit*>("textedit_subject");
    QTextBrowser* responseField = mainWindow->findChild<QTextBrowser*>("textbox_response");

    QVERIFY(queryField->toPlainText().isEmpty());
    QVERIFY(responseField->toPlainText().isEmpty());

    // QVERIFY(mainWindow->ui->textedit_subject->toPlainText().isEmpty());
    // QVERIFY(mainWindow->ui->textbox_response->toPlainText().isEmpty());
}

void TestMainWindow::testGenerateButton()
{
    QPlainTextEdit* queryField = mainWindow->findChild<QPlainTextEdit*>("textedit_subject");
    queryField->setPlainText("Post about C++");

    QPushButton* generateButton = mainWindow->findChild<QPushButton*>("pushButton_generate");
    QTest::mouseClick(generateButton, Qt::LeftButton);

    // Wait for the slot to finish execution
    QTest::qWait(10000);

    // Check if the response is not empty
    QTextBrowser* responseField = mainWindow->findChild<QTextBrowser*>("textbox_response");
    QVERIFY(!responseField->toPlainText().isEmpty());
}

void TestMainWindow::testResetButton()
{
    QPlainTextEdit* queryField = mainWindow->findChild<QPlainTextEdit*>("textedit_subject");
    QTextBrowser* responseField = mainWindow->findChild<QTextBrowser*>("textbox_response");
    queryField->setPlainText("Post about C++");
    responseField->setPlainText("Generated response");

    QPushButton* resetButton = mainWindow->findChild<QPushButton*>("pushButton_Reset");
    QTest::mouseClick(resetButton, Qt::LeftButton);

    // Check if query and response fields are empty after reset
    QVERIFY(queryField->toPlainText().isEmpty());
    QVERIFY(responseField->toPlainText().isEmpty());
}

void TestMainWindow::testDoneButton()
{
    QPushButton* doneButton = mainWindow->findChild<QPushButton*>("pushButton_Done");
    QVERIFY(doneButton != nullptr);
    // QTest::mouseClick(doneButton, Qt::LeftButton);
    // TODO: Fix mouseclick error

    // Check if query and response fields are empty after reset
    // QPlainTextEdit* queryField = mainWindow->findChild<QPlainTextEdit*>("textedit_subject");
    // QTextBrowser* responseField = mainWindow->findChild<QTextBrowser*>("textbox_response");
    // QVERIFY(queryField->toPlainText().isEmpty());
    // QVERIFY(responseField->toPlainText().isEmpty());
}

// void TestMainWindow::testCMSButton()
// {
//     mainWindow->ui->textbox_response->setPlainText("Post about C++");
//     QTest::mouseClick(mainWindow->ui->pushButton_CMS, Qt::LeftButton);

//     // What to check???
// }
