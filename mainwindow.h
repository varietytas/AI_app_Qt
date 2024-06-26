#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sendconfirmwindow.h"
#include "resetwarningwindow.h"
#include <QStringListModel>
#include "requestsToBackend.h"
#include <QNetworkReply>
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
    void newHistory();
    void replyMessage(QNetworkReply* reply);

private slots:
    void on_pushButton_Done_clicked();
    void on_pushButton_Reset_clicked();
    void on_textEdit_clicked(const QModelIndex& index);
    void on_pushButton_CMS_clicked();
    void on_pushButton_generate_clicked();
    void on_pushButton_prev_clicked();
    void on_pushButton_next_clicked();
    // void on_pushB1111utton_generate_clicked();

private:

    QStringListModel *model;
    Ui::MainWindow* ui;
    SendConfirmWindow scw;
    ResetWarningWindow rww;
    QList<QString> history;

    void resizeEvent(QResizeEvent*) override;
};

#endif // MAINWINDOW_H
