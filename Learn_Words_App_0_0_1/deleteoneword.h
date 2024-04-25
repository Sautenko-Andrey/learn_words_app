#ifndef DELETEONEWORD_H
#define DELETEONEWORD_H

#include <QDialog>
#include "common.h"
#include <memory>

namespace Ui {
class DeleteOneWord;
}

class DeleteOneWord : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteOneWord(QWidget *parent = nullptr);
    ~DeleteOneWord();

    DeleteOneWord(const DeleteOneWord &other);

    DeleteOneWord& operator=(const DeleteOneWord &other);

private slots:
    void on_deleteButton_clicked();

private:
    //Ui::DeleteOneWord *ui;
    std::unique_ptr<Ui::DeleteOneWord> ui;
    OpenDB db;
};

#endif // DELETEONEWORD_H
