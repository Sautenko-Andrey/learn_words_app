#ifndef DELETEWORD_H
#define DELETEWORD_H

#include <QDialog>
#include "common.h"

namespace Ui {
class DeleteWord;
}

class DeleteWord : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWord(QWidget *parent = nullptr);
    ~DeleteWord();

private slots:
    void on_deleteButton_clicked();

    void on_setButton_clicked();

private:
    Ui::DeleteWord *ui;

    OpenDB db;

    int mode_index;

    void make_delete_query(const QString &target_word, All_Modes mode);
};

#endif // DELETEWORD_H
