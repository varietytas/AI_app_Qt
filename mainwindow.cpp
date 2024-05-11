#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    ui->tabWidget->setFixedSize(size());
    QWidget::resizeEvent(event);
}


void MainWindow::defaultResize()
{
    // Get the dimension available on the screen
    QSize availableSize = qApp->screens()[0]->size();
    resize(availableSize);
}

void MainWindow::on_pushButton_Done_clicked()
{
    scw.show();
}

void MainWindow::on_pushButton_Reset_clicked()
{
    rww.show();
}

