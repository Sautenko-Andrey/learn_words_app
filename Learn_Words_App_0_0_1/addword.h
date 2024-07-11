#ifndef ADDWORD_H
#define ADDWORD_H

#include <QDialog>
#include "common.h"

namespace Ui {
class AddWord;
}

class AddWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddWord(QSqlDatabase &database, QWidget *parent = nullptr);
    ~AddWord();

private slots:
    void on_addButton_clicked();

    void on_selectButton_clicked();

    void on_clearLinesButton_clicked();

    void on_clearForeignButton_clicked();

    void on_clearRusButton_clicked();

    void on_fontUpButton_clicked();

    void on_fontDownButton_clicked();

private:
    Ui::AddWord *ui;

    void show_total_words();

    int getTotalWords();

    QSqlDatabase *db{nullptr};

    int mode_index;

    int font_size = 14;
};

#endif // ADDWORD_H
