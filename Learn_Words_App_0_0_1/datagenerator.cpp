#include "datagenerator.h"
#include <QMessageBox>
#include "common.h"

DataGenerator::DataGenerator(const QString &request_msg, const QString &path_to_flag,
                             QSqlQuery &query, QObject *parent)
    : QObject{parent},
      m_request_msg{request_msg},
      m_path_to_flag{path_to_flag},
      m_query{query}
{}

DataGenerator::~DataGenerator()
{

}

// void UserLearns::prepareData(const QString &request_msg,
//                              const QString &path_to_flag,
//                              QSqlQuery &query){

//     if(!query.exec(request_msg)){
//         QMessageBox::warning(this, "Error!",
//                              "Couldn't load data when preparing.");
//     }

//     // Set language flag
//     DrawLangLabel(ui->current_languageLabel, path_to_flag);

//     // let's clear data
//     all_words.clear();
//     ui->taskTextEdit->clear();

//     ui->progressBar->setValue(0);

//     // drop all counters
//     counter = 0;

//     right_answers = 0;

//     answers_counter = 0;

//     progress_steps = 1.0;

//     // fill with a new words
//     while(query.next()){
//         all_words.insert(query.value(0).toString(),
//                          query.value(1).toString());
//     }

//     // let's show the very first word(rus) to user
//     QString first_word = all_words.cbegin().value();
//     ui->taskTextEdit->setText(first_word);
//     ++counter;

//     // draw a result label with loading animation
//     waitingMovie();
// }

void DataGenerator::dataPrepare()
{
    if(!m_query.exec(m_request_msg)){
        QMessageBox::warning(this, "Error!", "Couldn't load data when preparing.");
    }

    // Set language flag
    DrawLangLabel(ui->current_languageLabel, path_to_flag);
}
