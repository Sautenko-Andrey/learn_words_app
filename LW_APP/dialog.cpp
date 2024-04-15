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


void Dialog::on_stats_button_clicked()
{
    QMessageBox::information(this, "Results", "Succesful answers: 100%");
    // let's return focus on the second lineEdit after closing dialog window
    ui->lineEdit_2->setFocus();
}

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
