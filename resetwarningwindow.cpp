#include "resetwarningwindow.h"
#include "ui_resetwarningwindow.h"

ResetWarningWindow::ResetWarningWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetWarningWindow)
{
    ui->setupUi(this);
}

ResetWarningWindow::~ResetWarningWindow()
{
    delete ui;
}
