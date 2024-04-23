#include "usersession.h"
#include "ui_usersession.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QtSql>

UserSession::UserSession(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserSession)
{
    ui->setupUi(this);

    // Let's make focus on user's edit line
    ui->userLineEdit->setFocus();

    // Let's set progress bar value equal to null
    ui->progressBar->setValue(0);

    // Let's show the tasks for the user
    QSqlQuery query(db.get_my_db());

    // rus -> eng mode
    // Showing to user the very first rus word from the data base
    query.prepare("SELECT rus_word FROM ENG_RUS_WORDS ORDER BY id LIMIT 1");

    if(!query.exec()){
        qDebug() << db.get_my_db().lastError().text();
    }

    // showing the task
    while(query.next()){
        ui->taskLineEdit->setText(query.value(0).toString());
    }


    while(query.next()){
        qDebug() << query.value(0);
    }

    // when user uses "Finish" button we close current learning session
    connect(ui->finishButton, SIGNAL(clicked(bool)), this, SLOT(close()));
}

UserSession::~UserSession()
{
    delete ui;
}

void UserSession::on_nextButton_clicked()
{
    // Let's clear a previous word(task)
    ui->taskLineEdit->clear();

    // let's clear user edit line
    ui->userLineEdit->clear();

    // let's show the progress by changing the progressBar value
    // Let's get a number of words in the data base
    QSqlQuery query(db.get_my_db());
    query.exec("SELECT COUNT(*) FROM ENG_RUS_WORDS");

    if(query.first()){

        // We display user's progress through progress bar
        unsigned total_words = query.value(0).toUInt();
        unsigned user_progress = (progress_steps / total_words) * 100;
        ui->progressBar->setValue(user_progress);

        // when all tasks are passed we show result to user
        if(static_cast<unsigned>(progress_steps) == total_words){
            QMessageBox::information(this, "Lesson is finished", "Rigth answers: 100 %");

            // and we make user edit line closed until user press button "Restart"
            ui->userLineEdit->setDisabled(true);
        }
        progress_steps += 1.0;
    }

    // let's show to user the next word(task)
    // let's make a new query
    QSqlQuery task_query(db.get_my_db());
    task_query.prepare("SELECT rus_word FROM ENG_RUS_WORDS ORDER BY id LIMIT 1 OFFSET :my_offset");
    task_query.bindValue(":my_offset", offset);
    if(!task_query.exec()){
        qDebug() << db.get_my_db().lastError().text();
        QMessageBox::information(this, "Error", "Couldn't load word from data base.");
        return;
    }
    else{
        // let's show the word
        while(task_query.next()){
            ui->taskLineEdit->setText(task_query.value(0).toString());
            //qDebug() << "rus word: " << task_query.value(0);
            ++offset; // if OK we increment counter offset
        }
    }

}
