#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sizes.h>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>
#include <QString>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <string>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->resize(static_cast<int>(Sizes::MAIN_WINDOW_IMAGE_LABEL),
                           static_cast<int>(Sizes::MAIN_WINDOW_IMAGE_LABEL));
    // Path to main image
    const QString path_main_image = QDir::homePath() +
                              "/learn_words_app/Learn_Words_App_0_0_1/main.jpeg";
    QPixmap pixmap(path_main_image);
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setMask(pixmap.mask());
}


MainWindow::~MainWindow()
{
    delete ui;
}


// Function activates the user learning session dialog
void MainWindow::on_actionStart_lesson_triggered()
{

    user_learns_session = std::make_unique<UserLearns>(db.get_my_db(), this);
    user_learns_session->show();
}


void MainWindow::on_actionAdd_word_triggered()
{
    // here we call add word widget
    add_word_session = std::make_unique<AddWord>(db.get_my_db(), this);
    add_word_session->show();
}


void MainWindow::on_actionStats_triggered()
{
    // here we call a Message box with user's result
    // in percentes
    // We create and call stats dialog
    user_stats_session = std::make_unique<UserStats>(db.get_my_db(), this);
    user_stats_session->setGeometry(0, 0,
                                      static_cast<int>(Sizes::STATS_DIALOG_WIDTH),
                                      static_cast<int>(Sizes::STATS_DIALOG_HEIGHT));
    user_stats_session->show();
}


void MainWindow::on_actionSet_word_triggered()
{
    set_one_word_session = std::make_unique<SetWord>(db.get_my_db(), this);
    set_one_word_session->setGeometry(0, 0,
                                      static_cast<int>(Sizes::DIALOG_WINDOW_WIDTH),
                                      static_cast<int>(Sizes::DIALOG_WINDOW_HEIGHT));
    set_one_word_session->show();
}


void MainWindow::on_actionDelete_word_triggered()
{
    // call the delete word dialog
    delete_word_session = std::make_unique<DeleteWord>(db.get_my_db(), this);
    delete_word_session->setGeometry(0, 0,
                                     static_cast<int>(Sizes::DIALOG_WINDOW_WIDTH),
                                     static_cast<int>(Sizes::DIALOG_WINDOW_HEIGHT));
    delete_word_session->show();
}


void MainWindow::on_actionFinish_lesson_triggered()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Confirm", "Wanna exit?",
                          QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes){
        close();
    }
}


void MainWindow::on_actionAdd_words_from_file_triggered()
{
    // get a file
    const QString file_path = QFileDialog::getOpenFileName(this, "Select a file");

    // work with file
    QFile file(file_path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this, "File error!", "Couldn't open a file");
        return;
    }

    QTextStream in(&file);

    // Adding words to the data_base
    // let's make a query
    QSqlQuery query(db.get_my_db());

    while(!in.atEnd()){
        QString temp = in.readLine();
        std::string line = temp.toStdString();

        auto res_index = line.find('*');

        if(res_index != std::string::npos){

            std::string rus{line.begin(), line.begin() + res_index};

            QString rus_word = QString::fromStdString(rus);

            std::string foreign{line.begin() + res_index + 1, line.end()};

            QString foreign_word = QString::fromStdString(foreign);

            query.prepare("INSERT INTO ENG_RUS_WORDS(eng_word, rus_word) "
                          "VALUES(:user_foreign_word, :user_rus_word)");

            query.bindValue(":user_foreign_word", foreign_word);
            query.bindValue(":user_rus_word", rus_word);

            if(!query.exec()){
                qDebug() << "Dublicated word / another issue. Word hasn't been added.";
            }
            else{
                qDebug() << "word has been added.";
            }
        }
        else{
            continue;
        }
    }

    file.close();
}
