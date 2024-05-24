#include "newloginwindow.h"
#include "ui_newloginwindow.h"
#include "mainwindow.h"

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
    QString password = ui->labelPassword->text();
    qDebug() << "Email: " << email;
    qDebug() << "Password: " << password;

    setCentralWidget(new MainWindow(this));
}