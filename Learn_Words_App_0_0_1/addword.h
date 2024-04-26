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
    explicit AddWord(QWidget *parent = nullptr);
    ~AddWord();

private slots:
    void on_addButton_clicked();

    void on_selectButton_clicked();

private:
    Ui::AddWord *ui;

    OpenDB db;

    void show_total_words();

    int mode_index;
};

#endif // ADDWORD_H
