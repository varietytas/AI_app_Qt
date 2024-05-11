#include "sendconfirmwindow.h"
#include "ui_sendconfirmwindow.h"

SendConfirmWindow::SendConfirmWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendConfirmWindow)
{
    ui->setupUi(this);
}

SendConfirmWindow::~SendConfirmWindow()
{
    delete ui;
}
