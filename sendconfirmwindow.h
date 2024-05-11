#ifndef SENDCONFIRMWINDOW_H
#define SENDCONFIRMWINDOW_H

#include <QDialog>

namespace Ui { class SendConfirmWindow; }

class SendConfirmWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SendConfirmWindow(QWidget* parent = nullptr);
    ~SendConfirmWindow();

private:
    Ui::SendConfirmWindow* ui;
};

#endif // SENDCONFIRMWINDOW_H
