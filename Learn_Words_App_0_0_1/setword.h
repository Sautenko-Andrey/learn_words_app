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

    void on_fontUpButton_clicked();

    void on_fontDownButton_clicked();

    void on_clearAllButton_clicked();

    void on_clearLeftButton_clicked();

    void on_clearRightButton_clicked();

private:
    Ui::SetWord *ui;

    QSqlDatabase *db;

    void makeSetQuery(const QString &corrupted_word,
                    const QString &correct_word, All_Modes mode);

    int mode_index;

    All_Modes current_mode;

    int font_size = 14;
};

#endif // SETWORD_H
