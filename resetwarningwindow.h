#ifndef RESETWARNINGWINDOW_H
#define RESETWARNINGWINDOW_H

#include <QDialog>

namespace Ui { class ResetWarningWindow; }

class ResetWarningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResetWarningWindow(QWidget* parent = nullptr);
    ~ResetWarningWindow();

private:
    Ui::ResetWarningWindow* ui;
};

#endif // RESETWARNINGWINDOW_H
