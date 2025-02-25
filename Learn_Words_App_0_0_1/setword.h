#ifndef SETWORD_H
#define SETWORD_H

#include <QDialog>
#include "common.h"
#include <QVector>
#include <QSqlQuery>

namespace Ui {
class SetWord;
}


class SetWord : public QDialog
{
    Q_OBJECT

public:
    explicit SetWord(QSqlDatabase &database, QWidget *parent = nullptr);
    ~SetWord();

private slots:

    void on_setButton_clicked();

    void on_selectButton_clicked();

    void on_fontUpButton_clicked();

    void on_fontDownButton_clicked();

    void on_clearAllButton_clicked();

    void on_clearLeftButton_clicked();

    void on_clearRightButton_clicked();

private:
    Ui::SetWord *ui;

    QSqlDatabase *db;

    template<typename T>
    void makeSetQuery(T &&corrupted_word,
                      T &&correct_word,
                      All_Modes mode);

    int mode_index;

    All_Modes current_mode;

    int font_size{14};
};


template<typename T>
void SetWord::makeSetQuery(T &&corrupted_word,
                           T &&correct_word,
                           All_Modes mode)
{
    // Make a query
    QSqlQuery query(*db);

    switch (mode) {
    case All_Modes::RUS__ENG_RUS:
        query.prepare("UPDATE ENG_RUS_WORDS SET "
                          "rus_word = :correct_data "
                          "WHERE rus_word = :corrupted_data");
        break;

    case All_Modes::ENG__ENG_RUS:
        query.prepare("UPDATE ENG_RUS_WORDS SET "
                          "eng_word = :correct_data "
                          "WHERE eng_word = :corrupted_data");
        break;

    case All_Modes::SWE__SWE_RUS:
        query.prepare("UPDATE SWE_RUS_WORDS SET "
                          "swe_word = :correct_data "
                          "WHERE swe_word = :corrupted_data");
        break;

    case All_Modes::RUS__SWE_RUS:
        query.prepare("UPDATE SWE_RUS_WORDS SET "
                          "rus_word = :correct_data "
                          "WHERE rus_word = :corrupted_data");
        break;
    }

    query.bindValue(":correct_data", std::move<T>(correct_word));
    query.bindValue(":corrupted_data", std::move<T>(corrupted_word));

    if(!query.exec()){
        qDebug() << "Error while setting a word in the data base!";
        QMessageBox::information(this, "Error!",
                                     "Data base corrupted. Try one more time.");
        return;
    }
    else{

        constexpr int miliseconds{2000};

        showTempMessage(QStringLiteral("Status"),
                        QStringLiteral("Word has been successfuly setted."),
                        miliseconds);
    }
}

#endif // SETWORD_H
