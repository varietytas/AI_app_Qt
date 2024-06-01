#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringListModel>
#include <QStringList>
#include <QCoreApplication>
#include <QUrl>
#include <QDesktopServices>
#include <iostream>
#include <QMessageBox>
#include "requestsToBackend.h"


QStringList mainGuidlist = {
    "Шаг 1: Добавьте нашего бота в ваш канал: [@ai_app_1_bot](https://t.me/ai_app_1_bot).",
    "Шаг 2: Отправьте сообщение боту [@LeadConverterToolkitBot](https://t.me/LeadConverterToolkitBot) и укажите ваш channel id (ID вашего Telegram-канала).", 
    "Шаг 3: На главной странице введите название вашего поста и нажмите кнопку \"Сгенерировать\".  Yandex GPT сгенерирует для вас текст.", 
    "Шаг 4: Используйте кнопки \"Reset\" для очистки текста или \"Generate\" для перегенерации нового варианта.", 
    "Шаг 5: Нажмите кнопку \"Edit\", зарегистрируйтесь в Strapi (если еще не сделали этого), войдите в проект \"Blogs\" и отформатируйте, отредактируйте пост. Сохраните изменения и опубликуйте пост в Strapi.", 
    "Шаг 6: Вернитесь в приложение AI APP и нажмите кнопку \"Done\": бот отправит ваш пост в ваш канал.", 
    "Шаг 7: Посмотреть историю ваших постов можно в Strapi или на специальной странице \"History\".", 
    "Шаг 8: Нажмите на название поста справа, и слева отобразится предыдущий пост.", 
    "Наслаждайтесь созданием контента с помощью AI APP!"
};
int lenMainGuidlist = mainGuidlist.size();
int currentGuid = 0;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QNetworkAccessManager *network =  new QNetworkAccessManager(this);
    QObject::connect(network, &QNetworkAccessManager::finished, this, &MainWindow::replyMessage);
    network -> get(QNetworkRequest(QUrl("https://qna.habr.com")));


    AuthUser user(QString("email"),QString("login"),QString("password"));
    QJsonObject token = user.get_token();
    QJsonDocument doc(token);
    QString jsonString = QString::fromUtf8(doc.toJson());
    //QMessageBox dialog;
    //dialog.setText(jsonString);
    //dialog.exec();
    QStringList list;
    model=new QStringListModel;
     
    list<<"Matan";
    list<<"Parrot";
    list<<"Dog";
    model->setStringList(list);
    ui->textEdit->setModel(model);
    
    connect(ui->pushButton_generate, &QPushButton::clicked, this, &MainWindow::on_pushButton_generate_clicked);

    
}

void MainWindow::replyMessage(QNetworkReply * reply)
{
//    std::cout << reply->readAll().toStdString();
//    qDebug() << reply->readAll();
    // QMessageBox dialog;
    // dialog.setText(reply->readAll());
    // dialog.exec();
}
void MainWindow::on_textEdit_clicked(const QModelIndex &index)
{
    QList<QString> newList = {"<h3>Let {xn} be a sequence of real numbers. A number L is the limit of the sequence {xn}, if the numbers in</h3><p>the sequence beco<del>me closer and closer to L — and not to any other number.</del></p><p><del>Formal definition:</del></p><blockquote>For any ε > 0<a href=\"http://youtube\"> ther</a>e exists a natural number N such that, for every natural number n > N,</blockquote><code>we have |xn − L| < ε.</code><p>The<b> sequence {xn} is said to converge to or tend to the limit L, written</b></p><h1>In symbols: ∀ε > 0 ∃N ∈ N ∀n > N : |xn − L| < ε</h1><p></p><p></p><ul><li>ewer</li></ul><ol><li>req</li></ol><h6>jk</h6>",  "Мой попугай сегодня выучил новое слово и теперь повторяет его без устали! Этот маленький разговорчивец стал настоящим центром внимания в нашем доме. Его яркие перья и веселое поведение всегда вызывают улыбку на лицах всех членов семьи.", "<div> <h2>Пост о собаке:</h2><p>Сегодня я решил попробовать новую добавку для своей собаки. Она содержит все необходимые витамины и минералы для здоровья моего питомца. Надеюсь, что это поможет ему чувствовать себя еще лучше и быть более активным!</p></div>"};
    ui->tableView->setHtml(newList[index.row()]);
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
    ui->textbox_response->clear();
    ui->textedit_subject->clear();
}

void MainWindow::on_pushButton_Reset_clicked()
{
    ui->textbox_response->clear();
    ui->textedit_subject->clear();
    rww.show();
}

void MainWindow::on_pushButton_CMS_clicked()
{
    QDesktopServices::openUrl(QUrl("http://localhost:1337/admin/content-manager/collection-types/api::blog.blog?page=1&pageSize=10&sort=name:ASC"));
}

QString get_respones_from_yandex_gpt(QString &text){
    AuthUser user(QString("email"),QString("login"),QString("password"));
    QString answerPost = user.get_post_text(text);
    user.make_strapi_post(answerPost);
    return answerPost;
}

void MainWindow::on_pushButton_generate_clicked()
{
    QString text = ui->textedit_subject->toPlainText();
    QString response = get_respones_from_yandex_gpt(text); 
    ui->textbox_response->setText(response); 

}
// void MainWindow::on_pushButton_prev_clicked()
// {
//     currentGuid = (currentGuid-1)%lenMainGuidlist;
//     if (currentGuid < 0) currentGuid = 0; 

//     QString text = mainGuidlist[currentGuid];
//     ui->textbox_guid->setHtml(text); 

// }
// void MainWindow::on_pushButton_next_clicked()
// {
    
//     QString text = mainGuidlist[currentGuid];
//     ui->textbox_guid->setHtml(text); 
//     currentGuid ++;
//     if (currentGuid == lenMainGuidlist) currentGuid = lenMainGuidlist-1;
// }

QString yourCoin ="100";
QString yourCur =" руб";
int yourMoney = 0;
void MainWindow::on_pushB1111utton_generate_clicked(){
    yourMoney += rand() % 1000;
    QString moneyYourStr = QString::number(yourMoney);
    if (yourMoney >= 10000){
        yourCur =" $";
        yourMoney = 0;
        scw.show();
    }
        
    // std::string stryourCoin1 = "43";
    // QString text = stryourCoin1;
    ui->textbox_response_2->setText(moneyYourStr +yourCur); 
}
