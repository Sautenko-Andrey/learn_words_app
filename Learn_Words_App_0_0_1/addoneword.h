#ifndef ADDONEWORD_H
#define ADDONEWORD_H

#include <QDialog>
#include "opendb.h"
#include <memory>

namespace Ui {
class AddOneWord;
}

class AddOneWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddOneWord(QWidget *parent = nullptr);

    ~AddOneWord();

    AddOneWord(const AddOneWord &other);

    AddOneWord& operator=(const AddOneWord &other);

private slots:
    void on_addButton_clicked();

private:
    std::unique_ptr<Ui::AddOneWord> ui;
    OpenDB db;

    void show_total_words();
};

#endif // ADDONEWORD_H
