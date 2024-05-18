#include "deleteword.h"
#include "ui_deleteword.h"
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QDebug>

DeleteWord::DeleteWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteWord)
{
    ui->setupUi(this);

    // Show to user what he has to type in edit lines
    ui->textEdit->setPlaceholderText(QString("type word for deleting"));

    // let's make the focus on the "Select" button
    ui->setButton->setFocus();

    // make edit line unaccessable
    ui->textEdit->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->modeComboBox->addItem(mode);
    }
}

DeleteWord::~DeleteWord()
{
    delete ui;
}

void DeleteWord::on_deleteButton_clicked()
{
    // Action when user clickes on delete button
    // let's read users data from edit lines
    // get rid of unwanted leading and traling spaces
    QString target_word = (ui->textEdit->toPlainText()).trimmed();

    // depened of mode we set a desired word
    switch (mode_index) {
    case static_cast<int>(All_Modes::RUS__ENG_RUS):
        // let's delete rus word in eng-rus data base
        make_delete_query(target_word, All_Modes::RUS__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::ENG__ENG_RUS):
        // let's delete eng word in eng-rus data base
        make_delete_query(target_word, All_Modes::ENG__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::SWE__SWE_RUS):
        // let's delete swedish word in swe-rus data base
        make_delete_query(target_word, All_Modes::SWE__SWE_RUS);
        break;

    case static_cast<int>(All_Modes::RUS__SWE_RUS):
        // let's delete rus word in swe-rus data base
        make_delete_query(target_word, All_Modes::RUS__SWE_RUS);
        break;
    }

    // clear all edit lines
    ui->textEdit->clear();

    // make "Set" button accessable
    ui->setButton->setDefault(false);

    // make focus on the line edit
    ui->textEdit->setFocus();
}


void DeleteWord::on_setButton_clicked()
{
    // make edit lines and "Delete" button accessable
    ui->textEdit->setDisabled(false);
    ui->textEdit->setDisabled(false);

    // make edit line on focus
    ui->textEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->modeComboBox->currentIndex();
}

void DeleteWord::make_delete_query(const QString &target_word, All_Modes mode)
{
    // Make a query
    QSqlQuery query(db.get_my_db());

    switch (mode) {
    case All_Modes::RUS__ENG_RUS:
        query.prepare("DELETE FROM ENG_RUS_WORDS WHERE "
                      "rus_word = :targed_data");
        break;

    case All_Modes::ENG__ENG_RUS:
        query.prepare("DELETE FROM ENG_RUS_WORDS WHERE "
                      "eng_word = :targed_data");
        break;

    case All_Modes::SWE__SWE_RUS:
        query.prepare("DELETE FROM SWE_RUS_WORDS WHERE "
                      "swe_word = :targed_data");
        break;

    case All_Modes::RUS__SWE_RUS:
        query.prepare("DELETE FROM SWE_RUS_WORDS WHERE "
                      "rus_word = :targed_data");
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
