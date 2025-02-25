#include "deleteword.h"
#include "ui_deleteword.h"
#include <QSqlQuery>
#include <QtSql>
#include <QString>
#include <QStringLiteral>


DeleteWord::DeleteWord(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DeleteWord)
{
    ui->setupUi(this);

    // pointer on the database
    db = &database;

    // Show to user what he has to type in edit lines
    ui->textEdit->setPlaceholderText(QString("type word for deleting"));

    // let's make the focus on the "Select" button
    ui->setButton->setFocus();

    // make edit line and all buttons unaccessable
    // except select mode button
    // untill user chooses mode
    ui->textEdit->setDisabled(true);
    ui->deleteButton->setDisabled(true);
    ui->fontDownButton->setDisabled(true);
    ui->fontUpButton->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->modeComboBox->addItem(mode);
    }

    // buttons views
    // confirm selection button
    makeButtonIcon(QString(":all_pics/confirm.png"),
                   QString("Confirm selection"),
                   ui->setButton);

    // delete button
    makeButtonIcon(QString(":all_pics/delete.png"),
                   QString("Delete the word"),
                   ui->deleteButton);

    // font up button
    makeButtonIcon(QString(":all_pics/font_up.png"),
                   QString("Make text bigger"),
                   ui->fontUpButton);

    // font down button
    makeButtonIcon(QString(":all_pics/font_down.png"),
                   QString("Make text smaller"),
                   ui->fontDownButton);
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
        makeDeleteQuery(target_word, All_Modes::RUS__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::ENG__ENG_RUS):
        // let's delete eng word in eng-rus data base
        makeDeleteQuery(target_word, All_Modes::ENG__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::SWE__SWE_RUS):
        // let's delete swedish word in swe-rus data base
        makeDeleteQuery(target_word, All_Modes::SWE__SWE_RUS);
        break;

    case static_cast<int>(All_Modes::RUS__SWE_RUS):
        // let's delete rus word in swe-rus data base
        makeDeleteQuery(target_word, All_Modes::RUS__SWE_RUS);
        break;
    }

    // clear all edit lines
    ui->textEdit->clear();

    // make set button unaccessable
    ui->setButton->setDefault(false);

    // make focus on the line edit
    ui->textEdit->setFocus();
}


void DeleteWord::on_setButton_clicked()
{
    // make edit line and all buttons accessable again
    ui->textEdit->setDisabled(false);
    ui->textEdit->setDisabled(false);
    ui->deleteButton->setDisabled(false);
    ui->fontDownButton->setDisabled(false);
    ui->fontUpButton->setDisabled(false);

    // make edit line on focus
    ui->textEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->modeComboBox->currentIndex();
}

void DeleteWord::makeDeleteQuery(const QString &target_word, All_Modes mode)
{
    // Make a query
    QSqlQuery query(*db);

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

        constexpr int miliseconds{2000};

        showTempMessage(QString("Status"),
                        QString("Word has been successfuly deleted."),
                        miliseconds);
    }
}


void DeleteWord::on_fontUpButton_clicked()
{
    // makes text bigger
    setTextEditCursor(font_size, ui->textEdit, this);
}


void DeleteWord::on_fontDownButton_clicked()
{
    // makes text smaller
    setTextEditCursor(font_size, ui->textEdit, this, false);
}

