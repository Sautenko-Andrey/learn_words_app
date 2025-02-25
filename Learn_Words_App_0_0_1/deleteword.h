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
    explicit DeleteWord(QSqlDatabase &database, QWidget *parent = nullptr);
    ~DeleteWord();

private slots:
    void on_deleteButton_clicked();

    void on_setButton_clicked();

    void on_fontUpButton_clicked();

    void on_fontDownButton_clicked();

private:
    Ui::DeleteWord *ui;

    QSqlDatabase *db{nullptr};

    void makeDeleteQuery(const QString &target_word, All_Modes mode);

    int mode_index;

    int font_size{14};
};

#endif // DELETEWORD_H
