#ifndef ADDONEWORD_H
#define ADDONEWORD_H

#include <QDialog>
#include "opendb.h"

namespace Ui {
class AddOneWord;
}

class AddOneWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddOneWord(QWidget *parent = nullptr);
    ~AddOneWord();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddOneWord *ui;
    OpenDB db;
};

#endif // ADDONEWORD_H
