#include "addword.h"
#include "ui_addword.h"
#include <QString>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

AddWord::AddWord(QSqlDatabase &database, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddWord)
{
    ui->setupUi(this);

    // pointer on the database
    db = &database;

    // let's block access to the all buttons and text edits
    // except "Select language mode button" and give it when user will choose a mode.
    ui->leftTextEdit->setDisabled(true);
    ui->rightTextEdit->setDisabled(true);
    ui->addButton->setDisabled(true);
    ui->clearForeignButton->setDisabled(true);
    ui->clearRusButton->setDisabled(true);
    ui->clearLinesButton->setDisabled(true);
    ui->fontDownButton->setDisabled(true);
    ui->fontUpButton->setDisabled(true);

    // Show to user what he has type in edit lines
    ui->leftTextEdit->setPlaceholderText(QString("type foreign word"));
    ui->rightTextEdit->setPlaceholderText(QString("type russian word"));

    // let's show a number of words in current data base
    showTotalWords();

    // Make focus on modes select
    ui->selectButton->setFocus();

    // let's add all modes to the modes combobox
    for(const auto &mode : LANGUAGES_DB){
        ui->modeComboBox->addItem(mode);
    }

    // making icons for buttons
    // add button
    makeButtonIcon(QString(":all_pics/add.png"),
                   QString("Add a new word"),
                   ui->addButton);

    // clear all button
    makeButtonIcon(QString(":all_pics/clear_all.png"),
                   QString("Clear all lines"),
                   ui->clearLinesButton);

    // clear left line button
    makeButtonIcon(QString(":all_pics/clear_f.png"),
                   QString("Clear the left line"),
                   ui->clearForeignButton);

    // clear right line button
    makeButtonIcon(QString(":all_pics/clear_r.png"),
                   QString("Clear the right line"),
                   ui->clearRusButton);

    // confirm selection button
    makeButtonIcon(QString(":all_pics/confirm.png"),
                   QString("Confirm selection"),
                   ui->selectButton);

    // font up button
    makeButtonIcon(QString(":all_pics/font_up.png"),
                   QString("Make text bigger"),
                   ui->fontUpButton);

    // font down button
    makeButtonIcon(QString(":all_pics/font_down.png"),
                   QString("Make text smaller"),
                   ui->fontDownButton);

    // Set tool tip for the words counter
    ui->lcdNumber->setToolTip(QString("Total words"));
}


AddWord::~AddWord()
{
    delete ui;
}


void AddWord::on_addButton_clicked()
{
    // Let's check if the addition string/s is/are not empty
    if(ui->leftTextEdit->toPlainText().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as english word");
        return;
    }
    if(ui->rightTextEdit->toPlainText().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as russian word");
        return;
    }

    // set focus on the eng line edit
    ui->leftTextEdit->setFocus();

    // let's read words from line edits
    // let's get rid of potential unwanted leading and trailing characters
    // in this case spaces
    const auto user_foreign_word = (ui->leftTextEdit->toPlainText()).trimmed();
    const auto user_rus_word = (ui->rightTextEdit->toPlainText()).trimmed();

    // Adding word to the data_base
    // let's make a query
    QSqlQuery query(*db);

    if(mode_index == static_cast<int>(All_Languges::ENG)){
        query.prepare("INSERT INTO ENG_RUS_WORDS(eng_word, rus_word) "
                      "VALUES(:user_foreign_word, :user_rus_word)");
    }
    else{
        query.prepare("INSERT INTO SWE_RUS_WORDS(swe_word, rus_word) "
                      "VALUES(:user_foreign_word, :user_rus_word)");
    }

    query.bindValue(":user_foreign_word", user_foreign_word);
    query.bindValue(":user_rus_word", user_rus_word);

    if(!query.exec()){
        qDebug() << "Error while adding a new word to the data base!";
        QMessageBox::information(this, "Error!",
                                 "Data base corrupted. Try one more time.");
        return;
    }
    else{

        constexpr int miliseconds{1000};

        showTempMessage(QString("Status"),
                        QString("A new word has been successfuly added."),
                        miliseconds);
    }

    // let's clean both edit lines
    ui->leftTextEdit->clear();
    ui->rightTextEdit->clear();

    // let's show total words
    // before that we should flush old value
    showTotalWords();
}


void AddWord::on_selectButton_clicked()
{
    // make edit lines and "Add" button accessable
    ui->leftTextEdit->setDisabled(false);
    ui->rightTextEdit->setDisabled(false);
    ui->addButton->setDisabled(false);
    ui->clearForeignButton->setDisabled(false);
    ui->clearRusButton->setDisabled(false);
    ui->clearLinesButton->setDisabled(false);
    ui->fontDownButton->setDisabled(false);
    ui->fontUpButton->setDisabled(false);

    // make the first edit line on focus
    ui->leftTextEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->modeComboBox->currentIndex();

    // let's show a number of words in current data base
    showTotalWords();

    // Focus on the first edit line
    ui->leftTextEdit->setFocus();
}

// Function counts how many words saved in particular data base
void AddWord::showTotalWords()
{
    // lcdNumber settings
    auto palette = ui->lcdNumber->palette();
    palette.setColor(palette.WindowText, Qt::black);
    ui->lcdNumber->setPalette(palette);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->display(getTotalWords());
}


int AddWord::getTotalWords()
{
    QSqlQuery query(*db);

    if(mode_index == static_cast<int>(All_Languges::SWE)){
        query.exec("SELECT COUNT(*) FROM SWE_RUS_WORDS");
    }
    else{
        query.exec("SELECT COUNT(*) FROM ENG_RUS_WORDS");
    }

    if(query.first()){
        return query.value(0).toInt();
    }

    return -1;
}

// clear both lines (foreign language line and russian line)
void AddWord::on_clearLinesButton_clicked()
{
    ui->leftTextEdit->clear();
    ui->rightTextEdit->clear();
    ui->leftTextEdit->setFocus();
}


void AddWord::on_clearForeignButton_clicked()
{
    ui->leftTextEdit->clear();
    ui->leftTextEdit->setFocus();
}


void AddWord::on_clearRusButton_clicked()
{
    ui->rightTextEdit->clear();
    ui->rightTextEdit->setFocus();
}


void AddWord::on_fontUpButton_clicked()
{
    // makes text bigger
    setTextEditCursor(font_size, ui->leftTextEdit, ui->rightTextEdit, this);
}


void AddWord::on_fontDownButton_clicked()
{
    // makes text smaller
    setTextEditCursor(font_size, ui->leftTextEdit, ui->rightTextEdit, this, false);
}

