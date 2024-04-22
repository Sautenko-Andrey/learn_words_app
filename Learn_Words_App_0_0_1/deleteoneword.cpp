#include "deleteoneword.h"
#include "ui_deleteoneword.h"
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QDebug>

DeleteOneWord::DeleteOneWord(QWidget *parent)
    : QDialog(parent), ui(std::make_unique<Ui::DeleteOneWord>())

{
    ui->setupUi(this);

    // let's make the focus on the user's line
    ui->UserlineEdit->setFocus();
}

DeleteOneWord::~DeleteOneWord() = default;


DeleteOneWord::DeleteOneWord(const DeleteOneWord &other) : QDialog(), ui(nullptr)
{
    if(other.ui) ui = std::make_unique<Ui::DeleteOneWord>(*other.ui);
}

DeleteOneWord& DeleteOneWord::operator=(const DeleteOneWord &other)
{
    if(!other.ui) ui.reset();
    else if(!ui) ui = std::make_unique<Ui::DeleteOneWord>(*other.ui);
    else *ui = *other.ui;

    return *this;
}

void DeleteOneWord::on_deleteButton_clicked()
{
    // Action when user clickes on delete button

    // Let's read user's string
    QString user_word = ui->UserlineEdit->text();

    // Let's make a query
    QSqlQuery query(db.get_my_db());
    query.prepare("DELETE FROM ENG_RUS_WORDS WHERE eng_word=:target_word");
    query.bindValue(":target_word", user_word);

    if(!query.exec()){
        qDebug() << db.get_my_db().lastError().text();
        return;
    }

    // let's clear the user's edit line
    ui->UserlineEdit->clear();

}

