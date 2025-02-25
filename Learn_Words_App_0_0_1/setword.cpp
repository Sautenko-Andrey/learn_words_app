#include "setword.h"
#include "ui_setword.h"
#include <QDebug>
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

    // Make both edit lines and all buttons unaccessable
    // except set mode button
    ui->oldTextEdit->setDisabled(true);
    ui->newTextEdit->setDisabled(true);
    ui->setButton->setDisabled(true);
    ui->clearAllButton->setDisabled(true);
    ui->clearLeftButton->setDisabled(true);
    ui->clearRightButton->setDisabled(true);
    ui->fontDownButton->setDisabled(true);
    ui->fontUpButton->setDisabled(true);

    // let's add all modes to the modes combobox
    for(const auto &mode : MODES){
        ui->mode_comboBox->addItem(mode);
    }

    // buttons views
    // confirm selection button
    makeButtonIcon(QString(":all_pics/confirm.png"),
                   QString("Confirm selection"),
                   ui->selectButton);

    // confirm set button
    makeButtonIcon(QString(":all_pics/update.png"),
                   QString("Update the word"),
                   ui->setButton);

    // font up button
    makeButtonIcon(QString(":all_pics/font_up.png"),
                   QString("Make text bigger"),
                   ui->fontUpButton);

    // font down button
    makeButtonIcon(QString(":all_pics/font_down.png"),
                   QString("Make text smaller"),
                   ui->fontDownButton);

    // clear all button
    makeButtonIcon(QString(":all_pics/clear_all.png"),
                   QString("Clear all lines"),
                   ui->clearAllButton);

    // clear left line button
    makeButtonIcon(QString(":all_pics/clear_f.png"),
                   QString("Clear left line"),
                   ui->clearLeftButton);

    // clear right line button
    makeButtonIcon(QString(":all_pics/clear_r.png"),
                   QString("Clear right line"),
                   ui->clearRightButton);
}

SetWord::~SetWord()
{
    delete ui;
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
        makeSetQuery(corrupted_word, correct_word, All_Modes::RUS__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::ENG__ENG_RUS):
        // let's update eng word in eng-rus data base
        makeSetQuery(corrupted_word, correct_word, All_Modes::ENG__ENG_RUS);
        break;

    case static_cast<int>(All_Modes::SWE__SWE_RUS):
        // let's update swedish word in swe-rus data base
        makeSetQuery(corrupted_word, correct_word, All_Modes::SWE__SWE_RUS);
        break;

    case static_cast<int>(All_Modes::RUS__SWE_RUS):
        // let's update rus word in swe-rus data base
        makeSetQuery(corrupted_word, correct_word, All_Modes::RUS__SWE_RUS);
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
    // make both edit lines and all buttons accessable
    ui->oldTextEdit->setDisabled(false);
    ui->newTextEdit->setDisabled(false);
    ui->setButton->setDisabled(false);
    ui->clearAllButton->setDisabled(false);
    ui->clearLeftButton->setDisabled(false);
    ui->clearRightButton->setDisabled(false);
    ui->fontDownButton->setDisabled(false);
    ui->fontUpButton->setDisabled(false);

    // make first edit line on focus
    ui->oldTextEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->mode_comboBox->currentIndex();
}

void SetWord::on_fontUpButton_clicked()
{
    // make text bigger
    setTextEditCursor(font_size, ui->oldTextEdit, ui->newTextEdit, this);
}


void SetWord::on_fontDownButton_clicked()
{
    // make text smaller
    setTextEditCursor(font_size, ui->oldTextEdit, ui->newTextEdit, this, false);
}


void SetWord::on_clearAllButton_clicked()
{
    // clear text in both lines
    ui->oldTextEdit->clear();
    ui->newTextEdit->clear();
}


void SetWord::on_clearLeftButton_clicked()
{
    // clear text in the left line
    ui->oldTextEdit->clear();
}


void SetWord::on_clearRightButton_clicked()
{
    // clear text in the right line
    ui->newTextEdit->clear();
}

