#include "setword.h"
#include "ui_setword.h"
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

SetWord::SetWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetWord)
{
    ui->setupUi(this);

    // Make focus on the mode box
    ui->mode_comboBox->setFocus();

    // Show to user what he has to type in edit lines
    ui->word_for_correctLine->setPlaceholderText(QString("type incorrect word"));
    ui->new_wordLine->setPlaceholderText(QString("type correct word"));

    // Make both edit lines and "Set" button unaccessable
    ui->word_for_correctLine->setDisabled(true);
    ui->new_wordLine->setDisabled(true);
    ui->setButton->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->mode_comboBox->addItem(mode);
    }
}

SetWord::~SetWord()
{
    delete ui;
}


void SetWord::make_set_query(const QString &corrupted_word,
                         const QString &correct_word, All_Modes mode)
{

    // Make a query
    QSqlQuery query(db.get_my_db());

    switch (mode) {
    case All_Modes::RUS__ENG_RUS:
        query.prepare("UPDATE ENG_RUS_WORDS SET "
                      "rus_word = :correct_data "
                      "WHERE rus_word = :corrupted_data");
        break;

    case All_Modes::ENG__ENG_RUS:
        query.prepare("UPDATE ENG_RUS_WORDS SET "
                      "eng_word = :correct_data "
                      "WHERE eng_word = :corrupted_data");
        break;

    case All_Modes::SWE__SWE_RUS:
        query.prepare("UPDATE SWE_RUS_WORDS SET "
                      "swe_word = :correct_data "
                      "WHERE swe_word = :corrupted_data");
        break;

    case All_Modes::RUS__SWE_RUS:
        query.prepare("UPDATE SWE_RUS_WORDS SET "
                      "rus_word = :correct_data "
                      "WHERE rus_word = :corrupted_data");
        break;
    }

    query.bindValue(":correct_data", correct_word);
    query.bindValue(":corrupted_data", corrupted_word);

    if(!query.exec()){
        qDebug() << "Error while setting a word in the data base!";
        QMessageBox::information(this, "Error!",
                                 "Data base corrupted. Try one more time.");
        return;
    }
    else{
        ShowTempMessage("Status", "Word has been successfuly setted.", 2000);
    }
}


void SetWord::on_setButton_clicked()
{
    // let's read users data from edit lines
    QString corrupted_word = ui->word_for_correctLine->text();
    QString correct_word = ui->new_wordLine->text();

    // depened of mode we set a desired word
    switch (mode_index) {
    case All_Modes::RUS__ENG_RUS:
        // let's update rus word in eng-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::RUS__ENG_RUS);
        break;

    case All_Modes::ENG__ENG_RUS:
        // let's update eng word in eng-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::ENG__ENG_RUS);

        break;

    case All_Modes::SWE__SWE_RUS:
        // let's update swedish word in swe-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::SWE__SWE_RUS);
        break;

    case All_Modes::RUS__SWE_RUS:
        // let's update rus word in swe-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::RUS__SWE_RUS);
        break;
    }

    // clear all edit lines
    ui->word_for_correctLine->clear();
    ui->new_wordLine->clear();

    // make "Set" button accessable
    ui->setButton->setDefault(false);

    // make focus on the first line edit
    ui->word_for_correctLine->setFocus();

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

