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

private:
    Ui::AddWord *ui;

    //OpenDB db;

    QSqlDatabase *db{nullptr};

    void show_total_words();

    int getTotalWords();

    int mode_index;
};

#endif // ADDWORD_H
