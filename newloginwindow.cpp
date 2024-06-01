#include "newloginwindow.h"
#include "ui_newloginwindow.h"
#include "mainwindow.h"
#include "database.h"
#include <QCryptographicHash>
#include "requestsToBackend.h"
NewLoginWindow::NewLoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::NewLoginWindow)
{
    ui->setupUi(this);
}

NewLoginWindow::~NewLoginWindow()
{
    delete ui;
}

QString hashPassword(const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex();
}

void NewLoginWindow::on_pushButtonLogin_clicked()
{
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;
    Database db;
    db.createTables();
    std::string email1 = email.toStdString();
    std::string hashedPassword = password.toStdString();
//    if (db.getUserByEmailAndPassword(email1, hashedPassword))
//    {
//        setCentralWidget(new MainWindow(this));
//    }
    AuthUser user(email,password,password);
    bool exists = user.checkIfUserExists();
    if (exists){
        setCentralWidget(new MainWindow(this));
    }
    else{
        qDebug() << "User does not exist";
    }


}

void NewLoginWindow::on_pushButtonRegister_clicked()
{
    QString name = ui->lineEditname->text();
    QString email = ui->lineEditemailreg->text();
    QString password = ui->lineEditPassword_1->text();
    QString channel = ui->lineEditchannel->text();
    
    // qDebug() << "Email: " << email;
    // qDebug() << "Password: " << password;
    // qDebug() << "channel: " << channel;
    // qDebug() << "name: " << name;
    Database db;
    std::string email1 = email.toStdString();
    std::string hashedPassword = hashPassword(password).toStdString();
    // qDebug() << "Password: " << hashedPassword;
    std::string channel1 = channel.toStdString();
    std::string name1 = name.toStdString();
    db.addText(name1, email1, channel1, hashedPassword);
    AuthUser newUser = *new AuthUser(email,password,name);
    newUser.get_code();

    setCentralWidget(new MainWindow(this));
}
