#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <all_sizes.h>
#include <QMessageBox>
#include <QPixmap>
#include <QDir>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->resize(626, 626);
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
    user_session = std::make_unique<UserSession>(this);
    user_session->show();
}


void MainWindow::on_actionAdd_word_triggered()
{
    // here we call add word widget
    add_word_session = std::make_unique<AddWord>(this);
    add_word_session->show();
}


void MainWindow::on_actionStats_triggered()
{
    // here we call a Message box with user's result
    // in percentes
    QMessageBox::information(this, "Result", "Successful answers: 100 %");
}


void MainWindow::on_actionSet_word_triggered()
{
    set_one_word_session = std::make_unique<SetWord>(this);
    set_one_word_session->show();
}


void MainWindow::on_actionDelete_word_triggered()
{
    // call the delete word dialog
    delete_word_session = std::make_unique<DeleteWord>(this);
    delete_word_session->show();
}


void MainWindow::on_actionChange_mode_triggered()
{
    change_lesson_mode_session = std::make_unique<ChangeLessonMode>(this);
    change_lesson_mode_session->show();
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

