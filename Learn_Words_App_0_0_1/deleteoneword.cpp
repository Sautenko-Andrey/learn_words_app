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

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->modecomboBox->addItem(mode);
    }
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

void DeleteOneWord::make_delete_query(const QString &target_word, All_Modes mode)
{
    // Make a query
    QSqlQuery query(db.get_my_db());

    switch (mode) {
    case All_Modes::RUS__ENG_RUS:
        query.prepare("DELETE FROM ENG_RUS_WORDS WHERE "
                      "WHERE rus_word = :targed_data");
        break;

    case All_Modes::ENG__ENG_RUS:
        query.prepare("DELETE FROM ENG_RUS_WORDS WHERE "
                      "WHERE eng_word = :targed_data");
        break;

    case All_Modes::SWE__SWE_RUS:
        query.prepare("DELETE FROM SWE_RUS_WORDS WHERE "
                      "WHERE swe_word = :targed_data");
        break;

    case All_Modes::RUS__SWE_RUS:
        query.prepare("DELETE FROM SWE_RUS_WORDS WHERE "
                      "WHERE rus_word = :targed_data");
        break;
    }

    query.bindValue(":targed_data", target_word);

    if(!query.exec()){
        qDebug() << "Error while deleting a word from the data base!";
        QMessageBox::information(this, "Error!",
                                 "Data base corrupted. Try one more time.");
        return;
    }
    else{
        ShowTempMessage("Status", "Word has been successfuly deleted.", 2000);
    }
}

