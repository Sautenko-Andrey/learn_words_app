#include "setword.h"
#include "ui_setword.h"
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

SetWord::SetWord(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetWord)
{
    ui->setupUi(this);

    // pointer on the database
    db = &database;

    // Make focus on the mode box
    ui->mode_comboBox->setFocus();

    // Show to user what he has to type in edit lines
    ui->oldTextEdit->setPlaceholderText(QString("type incorrect word"));
    ui->newTextEdit->setPlaceholderText(QString("type correct word"));

    // Make both edit lines and "Set" button unaccessable
    ui->oldTextEdit->setDisabled(true);
    ui->newTextEdit->setDisabled(true);
    ui->setButton->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->mode_comboBox->addItem(mode);
    }

    // buttons views
    // confirm selection button
    makeButtonIcon(":all_pics/confirm.png",
                   "Confirm selection", ui->selectButton);

    // confirm set button
    makeButtonIcon(":all_pics/update.png",
                   "Update the word", ui->setButton);
}

SetWord::~SetWord()
{
    delete ui;
}


void SetWord::make_set_query(const QString &corrupted_word,
                         const QString &correct_word, All_Modes mode)
{

    // Make a query
    // QSqlQuery query(db.get_my_db());

    QSqlQuery query(*db);

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
    // get rid of leading and trailing unwanted spaces
    QString corrupted_word = (ui->oldTextEdit->toPlainText()).trimmed();
    QString correct_word = (ui->newTextEdit->toPlainText()).trimmed();

    // depened of mode we set a desired word
    switch (mode_index) {
    case static_cast<int>(All_Modes::RUS__ENG_RUS):
        // let's update rus word in eng-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::RUS__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::ENG__ENG_RUS):
        // let's update eng word in eng-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::ENG__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::SWE__SWE_RUS):
        // let's update swedish word in swe-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::SWE__SWE_RUS);
        break;

    case static_cast<int>(All_Modes::RUS__SWE_RUS):
        // let's update rus word in swe-rus data base
        make_set_query(corrupted_word, correct_word, All_Modes::RUS__SWE_RUS);
        break;
    }

    // clear all edit lines
    ui->oldTextEdit->clear();
    ui->newTextEdit->clear();

    // make "Set" button accessable
    ui->setButton->setDefault(false);

    // make focus on the first line edit
    ui->oldTextEdit->setFocus();

}

void SetWord::on_selectButton_clicked()
{
    // make both edit lines and "Set" button accessable
    ui->oldTextEdit->setDisabled(false);
    ui->newTextEdit->setDisabled(false);
    ui->setButton->setDisabled(false);

    // make first edit line on focus
    ui->oldTextEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->mode_comboBox->currentIndex();
}
