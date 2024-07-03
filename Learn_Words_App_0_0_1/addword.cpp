#include "addword.h"
#include "ui_addword.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>

AddWord::AddWord(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddWord)
{
    ui->setupUi(this);

    // let's block access to the both edit lines and "Add" button
    // before user sets mode
    ui->textEdit->setDisabled(true);
    ui->textEdit_2->setDisabled(true);
    ui->addButton->setDisabled(true);

    // Show to user what he has type in edit lines
    ui->textEdit->setPlaceholderText(QString("type foreign word"));
    ui->textEdit_2->setPlaceholderText(QString("type russian word"));

    // let's show a number of words in current data base
    show_total_words();

    // Make focus on modes select
    ui->selectButton->setFocus();

    // let's add all modes to the modes combobox
    for(const auto &mode : LANGUAGES_DB){
        ui->modeComboBox->addItem(mode);
    }

    // making icons for buttons
    // add button
    makeButtonIcon(":all_pics/add.png", "Add a new word", ui->addButton);

    // clear all button
    makeButtonIcon(":all_pics/clear_all.png", "Clear all lines", ui->clearLinesButton);

    // clear left line button
    makeButtonIcon(":all_pics/clear_f.png",
                   "Clear the left line", ui->clearForeignButton);

    // clear right line button
    makeButtonIcon(":all_pics/clear_r.png",
                   "Clear the right line", ui->clearRusButton);

    // confirm selection button
    makeButtonIcon(":all_pics/confirm.png",
                   "Confirm selection", ui->selectButton);

    // Set tool tip for the words counter
    ui->lcdNumber->setToolTip(QString("Total words"));
}


AddWord::~AddWord()
{
    delete ui;
}


// void makeButtonIcon(const QString &img_path, const QString &tool_tip,
//                     const QAbstractButton *button){
//     QIcon icon;
//     icon.addPixmap(QPixmap(img_path), QIcon::Active, QIcon::On);
//     button->setIcon(icon);
//     button->setToolTip(tool_tip);
// }


void AddWord::on_addButton_clicked()
{
    // Let's check if the addition string/s is/are not empty
    if(ui->textEdit->toPlainText().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as english word");
        return;
    }
    if(ui->textEdit_2->toPlainText().isEmpty()){
        QMessageBox::information(this, "Warning",
                                 "You can't add an empty string as russian word");
        return;
    }

    // set focus on the eng line edit
    ui->textEdit->setFocus();

    // let's read words from line edits
    // let's get rid of potential unwanted leading and trailing characters
    // in this case spaces
    QString user_foreign_word = (ui->textEdit->toPlainText()).trimmed();
    QString user_rus_word = (ui->textEdit_2->toPlainText()).trimmed();

    // Adding word to the data_base
    // let's make a query
    QSqlQuery query(db.get_my_db());

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
        ShowTempMessage("Status", "A new word has been successfuly added.", 1000);
    }

    // let's clean both edit lines
    ui->textEdit->clear();
    ui->textEdit_2->clear();

    // let's show total words
    // before that we should flush old value
    //ui->counterLabel->clear();
    show_total_words();
}


void AddWord::on_selectButton_clicked()
{
    // make edit lines and "Add" button accessable
    ui->textEdit->setDisabled(false);
    ui->textEdit_2->setDisabled(false);
    ui->addButton->setDisabled(false);

    // make the first edit line on focus
    ui->textEdit->setFocus();

    // saving chosen mode by user
    mode_index = ui->modeComboBox->currentIndex();

    // let's show a number of words in current data base
    show_total_words();

    // Focus on the first edit line
    ui->textEdit->setFocus();
}

// Function counts how many words saved in particular data base
void AddWord::show_total_words()
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
    QSqlQuery query(db.get_my_db());

    if(mode_index == static_cast<int>(All_Languges::ENG)){
        query.exec("SELECT COUNT(*) FROM ENG_RUS_WORDS");
    }
    else{
        query.exec("SELECT COUNT(*) FROM SWE_RUS_WORDS");
    }

    if(query.first()){
        return query.value(0).toInt();
    }

    return -1;
}

// clear both lines (foreign language line and russian line)
void AddWord::on_clearLinesButton_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit->setFocus();
}


void AddWord::on_clearForeignButton_clicked()
{
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}


void AddWord::on_clearRusButton_clicked()
{
    ui->textEdit_2->clear();
    ui->textEdit_2->setFocus();
}

