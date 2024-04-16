#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QVector>
#include <QDebug>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <QFile>
#include <QTextStream>
#include <map>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    read_data_from_DB();

    // let's make focus on the second lineEdit by default
    ui->lineEdit_2->setFocus();

    // let's add modes to the combobox (modes for users)
    for(const auto &mode : modes){
        ui->comboBox->addItem(mode);
    }

    // when user pushes "Close" button
    connect(ui->exit_button, SIGNAL(clicked(bool)), SLOT(close()));
}


Dialog::~Dialog()
{
    delete ui;
}

// Function displays on edit line the very first word from the DB
void Dialog::display_first_word()
{
    auto iter = data_base.cbegin();
    std::advance(iter, counter);
    ui->lineEdit->setText(QString::fromStdString(iter->first));
    ++counter;
}

// Function prompts for the user choice
// The user can set a mode for a lesson
void Dialog::on_confirm_mode_clicked()
{

    // CHANGE qDebug() to the real logic!!!
    switch (ui->comboBox->currentIndex()) {
    case All_Modes::RUS_ENG:
        qDebug() << "RUS_ENG";
        break;
    case All_Modes::ENG_RUS:
        qDebug() << "ENG_RUS";
        break;
    case All_Modes::RUS_SWE:
        qDebug() << "RUS_SWE";
        break;
    case All_Modes::SWE_RUS:
        qDebug() << "SWE_RUS";
        break;
    }

    // let's return focus on the second lineEdit after closing dialog window
    ui->lineEdit_2->setFocus();
}

// Function displays a user's result when he/she pushes button "Stats"
// After closing this dialog window function returns focus on edit line
void Dialog::on_stats_button_clicked()
{
    QMessageBox::information(this, "Results", "Succesful answers: 100%");
    // let's return focus on the second lineEdit after closing dialog window
    ui->lineEdit_2->setFocus();
}

// Function reads the data from the DB
// and saves it into map,
// then displays the very first word for the user.
// Obviously, this is the start of the user's session
void Dialog::read_data_from_DB()
{
    std::ifstream input_stream("/home/andrey/eng_words_temp_db.txt");
    if(!input_stream){
        qDebug() << "Couldn't open a file for reading data from DB";
    }

    std::string temp_str;

    // reading a data from the file (temporary. data will be in DB soon)
    while(std::getline(input_stream, temp_str)){
        std::vector<std::string> words(2);
        // split text by ':' via boost
        boost::split(words, temp_str, boost::is_any_of(":"));
        data_base[words[0]] = words[1];
    }

    // let's show the first word for user
    QString first_word = QString::fromStdString(data_base.cbegin()->first);
    ui->lineEdit->setText(first_word);

}

// Function do logic when user pushes the button "Ok".
// It displays every time a next word
// and test user's answer is it correct or not
// save the results and then show it
// when user press "Stats" or the session ends.
void Dialog::on_pushButton_clicked()
{
    // when user pushes this button we should check
    // his answer and show him the next word
    // first of all let's check if counter less then words we have in the data base
    if(counter == data_base.size()){
        // save the last user's answer
        QString user_answer = ui->lineEdit_2->text();
        // test it
        qDebug() << user_answer;

        // we show user results
        QMessageBox::information(this, "Results", "Succesful answers: 100%");
        // let's clear line
        ui->lineEdit_2->clear();

        // let's block edit_line2 while user pushes restart
        ui->lineEdit_2->setDisabled(true);

        // let's make button "Ok" unaccessable
        ui->pushButton->setDisabled(true);

        return;
    }


    // let's read user's answer from the line
    QString user_answer = ui->lineEdit_2->text();
    // let's clear line
    ui->lineEdit_2->clear();
    // test it
    qDebug() << user_answer;

    // show for the user the very first word
    display_first_word();
}

// Function begins the session from the top
// when user pushes button "Restart".
void Dialog::on_pushButton_2_clicked()
{
    // Restart lesson from the top
    // make lineEdit_2 not disabled
    ui->lineEdit_2->setDisabled(false);

    // let's make button "Ok" accessable
    ui->pushButton->setDisabled(false);

    // let's make focus on edit line 2
    ui->lineEdit_2->setFocus();

    // counter must starts from the scratch
    counter = 0;

    // show for the user the very first word
    display_first_word();

}
