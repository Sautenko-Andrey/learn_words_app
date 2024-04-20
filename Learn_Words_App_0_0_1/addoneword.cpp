#include "addoneword.h"
#include "ui_addoneword.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <string>
#include <QtSql>
#include <QVariant>


AddOneWord::AddOneWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddOneWord)
{
    ui->setupUi(this);
}

AddOneWord::~AddOneWord()
{
    delete ui;
}


// Function addes a one new word into the data base
void AddOneWord::on_addButton_clicked()
{
    // set focus on the eng line edit
    ui->engLine->setFocus();

    // let's read words from line edits

    QString user_eng_word = ui->engLine->text();
    QString user_rus_word = ui->rusLine->text();

    // Adding word to the data_base
    // let's makea query
    QSqlQuery query(db.get_my_db());
    query.prepare("INSERT INTO ENG_RUS_WORDS(eng_word, rus_word) VALUES(:user_eng_word, :user_rus_word)");
    query.bindValue(":user_eng_word", user_eng_word);
    query.bindValue(":user_rus_word", user_rus_word);

    if(!query.exec()){
        qDebug() << db.get_my_db().lastError().text();
    }


    // let's clean both edit lines
    ui->engLine->clear();
    ui->rusLine->clear();

}

