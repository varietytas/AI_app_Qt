#include "newloginwindow.h"
#include "ui_newloginwindow.h"
#include "mainwindow.h"
#include "database.h"
#include <QCryptographicHash>
#include "requestsToBackend.h"
#include <QMainWindow>
#include <iostream>


NewLoginWindow::NewLoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewLoginWindow)
{
    ui->setupUi(this);
}

NewLoginWindow::~NewLoginWindow()
{
    delete ui;
}


void NewLoginWindow::on_pushButtonLogin_clicked()
{
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    AuthUser user(email, password, password);
    bool exists = user.checkIfUserExists();
    if (exists)
    {
        setCentralWidget(new MainWindow(this));
    }
    else
    {
        qDebug() << "User does not exist";
    }
}

void NewLoginWindow::on_pushButtonRegister_clicked()
{
    QString name = ui->lineEditname->text();
    QString email = ui->lineEditemailreg->text();
    QString password = ui->lineEditPassword_1->text();
    QString channel = ui->lineEditchannel->text();
    Database db;
    try
    {
        db.createTables();
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception in Making DB: " << e.what() << std::endl;
    }
    std::string email1 = email.toStdString();
    std::string password1 = password.toStdString();
    std::string channel1 = channel.toStdString();
    std::string name1 = name.toStdString();
    try
    {
        db.addText(name1, email1, channel1, password1);
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception in DB b/c of making new user: " << e.what() << std::endl;
    }

    AuthUser newUser = *new AuthUser(email, password, name);
    //    newUser.sendPost(email);
    QString answer = newUser.get_code(channel);
    // ответ либо ALREADY REGISTERED, что означает, что пользователь уже был зареган, или REGISTERED, значит, что все ок
    setCentralWidget(new MainWindow(this));
}
