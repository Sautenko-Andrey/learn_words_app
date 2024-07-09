#ifndef SETWORD_H
#define SETWORD_H

#include <QDialog>
#include "common.h"
#include <QVector>

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

private:
    Ui::SetWord *ui;

    //OpenDB db;

    QSqlDatabase *db;

    All_Modes current_mode;

    int mode_index;

    void make_set_query(const QString &corrupted_word,
                    const QString &correct_word, All_Modes mode);
};

#endif // SETWORD_H
