#ifndef NEWLOGINWINDOW_H
#define NEWLOGINWINDOW_H

#include <QMainWindow>
#include "sendconfirmwindow.h"
#include "resetwarningwindow.h"
namespace Ui {
class NewLoginWindow;
}

class NewLoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewLoginWindow(QWidget *parent = nullptr);
    ~NewLoginWindow();

private:
    Ui::NewLoginWindow *ui;
    SendConfirmWindow scw;
    ResetWarningWindow rww;
    
private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();
};

#endif // NEWLOGINWINDOW_H
