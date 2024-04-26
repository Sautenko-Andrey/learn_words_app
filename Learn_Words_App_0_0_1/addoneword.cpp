#include "addoneword.h"
#include "ui_addoneword.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>


AddOneWord::AddOneWord(QWidget *parent)
    : QDialog(parent), ui(std::make_unique<Ui::AddOneWord>())
{
    ui->setupUi(this);

    // let's show a number of words in current data base
    show_total_words();
}

AddOneWord::~AddOneWord() = default;

AddOneWord::AddOneWord(const AddOneWord &other) : QDialog(), ui(nullptr)
{
    if(other.ui) ui = std::make_unique<Ui::AddOneWord>(*other.ui);
}

AddOneWord& AddOneWord::operator=(const AddOneWord &other)
{
    if(!other.ui) ui.reset();
    else if(!ui) ui = std::make_unique<Ui::AddOneWord>(*other.ui);
    else *ui = *other.ui;

    return *this;
}


void AddOneWord::on_selectButton_clicked()
{
    qDebug() << "Select!";
}


// Function addes a one new word into the data base
void AddOneWord::on_addButton_clicked()
{
    // Let's check if the addition string/s is/are not empty
    if(ui->engLine->text().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as english word");
        return;
    }
    if(ui->rusLine->text().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as russian word");
        return;
    }


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

    // let's show total words
    // before that we should flush old value
    ui->words_counter_Label->clear();
    show_total_words();
}



void AddOneWord::show_total_words()
{
    QSqlQuery query(db.get_my_db());
    query.exec("SELECT COUNT(*) FROM ENG_RUS_WORDS");

    if(query.first()){
        QString total_words = query.value(0).toString();
        ui->words_counter_Label->setText("Total words: " + total_words);
    }
}
