#ifndef SETWORD_H
#define SETWORD_H

#include <QDialog>
#include "common.h"
#include <QVector>

namespace Ui {
class SetWord;
}

enum All_Modes{RUS__ENG_RUS, ENG__ENG_RUS, SWE__SWE_RUS, RUS__SWE_RUS};

class SetWord : public QDialog
{
    Q_OBJECT

public:
    explicit SetWord(QWidget *parent = nullptr);
    ~SetWord();

private slots:

    void on_setButton_clicked();

    void on_selectButton_clicked();

private:
    Ui::SetWord *ui;

    OpenDB db;

    const QVector<QString> modes = {
        "rus (eng-rus mode)",
        "eng (eng-rus mode)",
        "swe (swe-rus mode)",
        "rus (swe-rus mode)"
    };

    All_Modes current_mode;

    int mode_index;

    void make_set_query(QSqlQuery &query, const QString &data_base_name,
                        const QString &word_lang, const QString &corrupted_word,
                        const QString &correct_word);
};

#endif // SETWORD_H
