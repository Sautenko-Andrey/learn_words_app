#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <all_sizes.h>
#include <QMessageBox>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->imageLabel->resize(421, 341);
    QPixmap pixmap("/home/andrey/languages_6.jpg");
    ui->imageLabel->setPixmap(pixmap);
    ui->imageLabel->setMask(pixmap.mask());

    // when user pushes "finish lesson" we close the program
    // and show him his result
    connect(ui->actionFinish_lesson, SIGNAL(triggered(bool)), this, SLOT(close()));
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
    // add_one_word_session = std::make_unique<AddOneWord>(this);
    // add_one_word_session->resize(Sizes::ADD_WORD_DIALOG_WIDTH, Sizes::ADD_WORD_DIALOG_HEIGHT);
    // add_one_word_session->show();

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
    // del_one_word_session = std::make_unique<DeleteOneWord>(this);
    // del_one_word_session->show();
    delete_word_session = std::make_unique<DeleteWord>(this);
    delete_word_session->show();
}

