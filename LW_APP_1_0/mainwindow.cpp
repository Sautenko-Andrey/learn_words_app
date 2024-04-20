#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <vector>
#include <QString>
#include <QTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // read data from the DB
    read_data_from_DB();

    //let's show the first word (rus) for user
    QString first_word = QString::fromStdString(data_base.cbegin()->second);
    ui->lineTask->setText(first_word);
    ++counter;

    // let's make focus on lineTask
    ui->lineUser->setFocus();

    // let's set value of progressBar equal to zero
    ui->progressBar->setValue(0);

    // when user pushes "Close" button
    connect(ui->finishButton, SIGNAL(clicked(bool)), SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Function checks if the users answer is right
void MainWindow::answer_is_right(const QString &task, const QString &answer) noexcept
{
    ++answers_counter;
    if(task == answer){
        ++right_answers;
        ui->resultLabel->setText("+");
        ui->resultLabel->setStyleSheet("QLabel { color : green; }");
    }
    else{
        ui->resultLabel->setText("-");
        ui->resultLabel->setStyleSheet("QLabel { color : red; }");
    }

    // let's hide label after 2 seconds
    ui->resultLabel->setVisible(true);
    QTimer::singleShot(2000, ui->resultLabel, &QLabel::hide);

}

// Function displays on edit line word (rus) from the DB
void MainWindow::display_first_word()
{
    auto iter = data_base.cbegin();
    std::advance(iter, counter);

    // displays word for the user
    ui->lineTask->setText(QString::fromStdString(iter->second));

    ++counter;
}



// Function reads the data from the DB
// and saves it into map,
// then displays the very first word for the user.
// Obviously, this is the start of the user's session
void MainWindow::read_data_from_DB()
{
    std::ifstream input_stream("/home/andrey/eng_words_temp_db.txt");

    if(!input_stream){
        qDebug() << "Couldn't open a file for reading data from DB";
        return;
    }

    std::string temp_str;

    // reading a data from the file (temporary. data will be in DB soon)
    while(std::getline(input_stream, temp_str)){
        std::vector<std::string> words(2);
        // split text by ':' via boost
        boost::split(words, temp_str, boost::is_any_of(":"));
        data_base[words[0]] = words[1];
    }
}


// Function displays a user's result when he/she pushes button "Stats"
// After closing this dialog window function returns focus on edit line
void MainWindow::on_statsButton_clicked()
{
    QMessageBox::information(this, "Results", "Succesful answers: 100%");
    // let's return focus on the second lineEdit after closing dialog window
    ui->lineUser->setFocus();
}



// Function do logic when user pushes the button "Next".
// It displays every time a next word
// and test user's answer is it correct or not
// save the results and then show it
// when user press "Stats" or the session ends.
void MainWindow::on_nextButton_clicked()
{
    // when user pushes this button we should check
    // his answer and show him the next word

    // let's show the progress by changing the progressBar value
    unsigned user_progress = (steps / data_base.size()) * 100;
    qDebug() << user_progress;
    ui->progressBar->setValue(user_progress);
    steps += 1.0;

    // first of all let's check if counter less then words we have in the data base
    if(counter == data_base.size()){
        // save the last user's answer
        QString user_answer = ui->lineUser->text();

        // test it DELETE IT!
        qDebug() << user_answer;
        ////////////////////////////////

        // we have to check the very last user answer as well
        answer_is_right(QString::fromStdString((std::prev(data_base.cend()))->first), user_answer);


        // we show user results
        QMessageBox::information(this, "Results", "Succesful answers: 100%");

        // let's clear line
        ui->lineUser->clear();

        // let's block edit_line2 while user pushes restart
        ui->lineUser->setDisabled(true);

        // let's make button "Next" unaccessable
        ui->restartButton->setDisabled(true);

        return;
    }

    // let's read user's answer from the line
    QString user_answer = ui->lineUser->text();
    qDebug() << user_answer;

    // let's clear line
    ui->lineUser->clear();

    // show for the user the word
    display_first_word();

    // let's check user answer
    auto task = data_base.cbegin();
    std::advance(task, answers_counter);
    answer_is_right(QString::fromStdString(task->first), user_answer);
}


// Function begins the session from the top
// when user pushes button "Restart".
void MainWindow::on_restartButton_clicked()
{
    // Restart lesson from the top
    // make lineEdit_2 not disabled
    ui->lineUser->setDisabled(false);

    // let's make button "Next" accessable
    ui->nextButton->setDisabled(false);

    // let's make focus on edit line 2
    ui->lineUser->setFocus();

    // let/s make progress bar empty
    ui->progressBar->setValue(0);

    // let's make steps equal 1.0 again
    steps = 1.0;

    // counter must starts from the scratch
    counter = 0;

    // answers counter starts from the scratch as well
    answers_counter = 0;

    // show for the user the very first word
    display_first_word();
}

