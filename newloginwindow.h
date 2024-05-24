#ifndef NEWLOGINWINDOW_H
#define NEWLOGINWINDOW_H

#include <QMainWindow>

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
private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonRegister_clicked();
};

#endif // NEWLOGINWINDOW_H
