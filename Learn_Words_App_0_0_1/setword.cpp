#include "setword.h"
#include "ui_setword.h"
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>

SetWord::SetWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetWord)
{
    ui->setupUi(this);

    // Make focus on the mode box
    ui->mode_comboBox->setFocus();

    // Make both edit lines and "Set" button unaccessable
    ui->word_for_correctLine->setDisabled(true);
    ui->new_wordLine->setDisabled(true);
    ui->setButton->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : modes){
        ui->mode_comboBox->addItem(mode);
    }
}

SetWord::~SetWord()
{
    delete ui;
}


void SetWord::make_set_query(QSqlQuery &query, const QString &data_base_name,
                    const QString &word_lang, const QString &corrupted_word,
                    const QString &correct_word)
{
    query.prepare("UPDATE :data_base "
                  "SET :word = :correct_data WHERE :word = :corrupted_data");
    query.bindValue(":correct_data", correct_word);
    query.bindValue(":corrupted_data", corrupted_word);
    query.bindValue(":word", word_lang);
    query.bindValue(":data_base", data_base_name);
    if(!query.exec()){
        qDebug() << "Error while setting rus word in eng-rus mode";
    }
}


void SetWord::on_setButton_clicked()
{
    // let's read users data from edit lines
    QString corrupted_word = ui->word_for_correctLine->text();
    QString correct_word = ui->new_wordLine->text();

    // Make a query
    QSqlQuery query(db.get_my_db());

    //switch (current_mode) {
    switch (mode_index) {
    case All_Modes::RUS__ENG_RUS:
        // let's update rus word

        query.prepare("UPDATE ENG_RUS_WORDS "
                   "SET rus_word = :correct_data WHERE rus_word = :corrupted_data");
        query.bindValue(":correct_data", correct_word);
        query.bindValue(":corrupted_data", corrupted_word);
        if(!query.exec()){
            qDebug() << "Error while setting rus word in eng-rus mode\n"
                     << db.get_my_db().lastError().text();
        }
        // function doesn't wwork correctly!!! FIX IT!
        //---------------------------------------------------------------
        // make_set_query(query, "ENG_RUS_WORDS", "rus_word",
        //                corrupted_word, correct_word);
        //-------------------------------------------------------------

        break;

    case All_Modes::ENG__ENG_RUS:
        // let's update eng word

        query.prepare("UPDATE ENG_RUS_WORDS "
                      "SET eng_word = :correct_data WHERE eng_word = :corrupted_data");
        query.bindValue(":correct_data", correct_word);
        query.bindValue(":corrupted_data", corrupted_word);
        if(!query.exec()){
            qDebug() << "Error while setting eng word in eng-rus mode\n"
                     << db.get_my_db().lastError().text();
        }

        // make_set_query(query, "ENG_RUS_WORDS", "eng_word",
        //                corrupted_word, correct_word);

        break;

    case All_Modes::SWE__SWE_RUS:
        // let's update swedish word
        qDebug() << "Updating a swedish word in swe-rus mode";
        break;

    case All_Modes::RUS__SWE_RUS:
        // let's update rus word
        qDebug() << "Updating a rus word in swe-rus mode";
        break;
    }

    // clear all edit lines
    ui->word_for_correctLine->clear();
    ui->new_wordLine->clear();


}

void SetWord::on_selectButton_clicked()
{
    // make both edit lines and "Set" button accessable
    ui->word_for_correctLine->setDisabled(false);
    ui->new_wordLine->setDisabled(false);
    ui->setButton->setDisabled(false);

    // make first edit line on focus
    ui->word_for_correctLine->setFocus();

    // saving chosen mode by user
    mode_index = ui->mode_comboBox->currentIndex();
}

