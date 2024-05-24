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

    // setCentralWidget(new MainWindow(this));
    Database db;
    db.createTables();
    db.addText("1", "1", "1", "1");
    std::string email1 = email.toStdString();
    std::string password1 = password.toStdString();
    if (db.getUserByEmailAndPassword(email1,password1))
    {
        setCentralWidget(new MainWindow(this));
    }
}