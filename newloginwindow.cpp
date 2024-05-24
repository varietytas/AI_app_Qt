#include "newloginwindow.h"
#include "ui_newloginwindow.h"
#include "mainwindow.h"
#include "database.h"

NewLoginWindow::NewLoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NewLoginWindow)
{
    ui->setupUi(this);
}

NewLoginWindow::~NewLoginWindow()
{
    delete ui;
}
void NewLoginWindow::on_pushButtonLogin_clicked(){
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;
    Database db;
    std::string email1 = email.toStdString();
    std::string password1 = password.toStdString();
    if (db.getUserByEmailAndPassword(email1,password1))
    {
        setCentralWidget(new MainWindow(this));
    }
}

void NewLoginWindow::on_pushButtonRegister_clicked(){
    QString password = ui->lineEditPassword_1->text();
    QString channel = ui->lineEditchannel->text();
    QString email = ui->lineEditemailreg->text();
    QString name = ui->lineEditname->text();

    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;
    qDebug() << "channel: " << channel;
    qDebug() << "name: " << name;
    Database db;
    std::string email1 = email.toStdString();
    std::string password1 = password.toStdString();
    std::string channel1 = channel.toStdString();
    std::string name1 = name.toStdString();
    db.addText(name1, email1, channel1, password1);
    setCentralWidget(new MainWindow(this));

}