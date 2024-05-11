#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sendconfirmwindow.h"
#include "resetwarningwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void defaultResize();

private slots:
    void on_pushButton_Done_clicked();
    void on_pushButton_Reset_clicked();

private:
    Ui::MainWindow* ui;
    SendConfirmWindow scw;
    ResetWarningWindow rww;

    void resizeEvent(QResizeEvent*) override;
};

#endif // MAINWINDOW_H
